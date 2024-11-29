/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cahaik <cahaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 21:54:21 by cahaik            #+#    #+#             */
/*   Updated: 2024/11/29 00:28:03 by cahaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	heredocc(t_redirection *heredoc, t_ev *ev, t_status *p)
{
	static int	i;
	char		*tmp;

	tmp = ft_itoa(++i);
	heredoc->file = ft_strjoin("/tmp/heredocs", tmp);
	free(tmp);
	heredoc->fd = open(heredoc->file, O_CREAT | O_WRONLY, 0644);
	if (heredoc->fd < 0)
	{
		write (2, "minishell : ", 12);
		perror("open");
		p->exit_status = 1;
		exit (p->exit_status);
	}
	all_heredocs(heredoc, ev, p);
}

int	readline_loop(t_redirection *heredoc, t_ev *ev, t_status *p)
{
	char	*tmp;
	char	*input;

	input = NULL;
	tmp = NULL;
	while (1)
	{
		input = readline(">");
		if (!input)
			return (write(1, "\n", 1), 0);
		if (ft_strcmp(input, heredoc->delimiter_be4expand) == 0)
			return (free(input), 0);
		if (heredoc->hdoc_need_expand == 1)
		{
			tmp = hdoc_expand(input, ev, p);
			free(input); 
			input = tmp;
		}
		write(heredoc->fd, input, ft_strlen(input));
		write(heredoc->fd, "\n", 1);
		free(input);
	}
	return (0);
}

void	all_heredocs(t_redirection *heredoc, t_ev *ev, t_status *p)
{
	int		status;
	pid_t	pid;

	signal(SIGINT, SIG_IGN);
	status = 0;
	pid = fork();
	if (pid < 0)
		fork_failed(p);
	else if (pid == 0)
	{
		signals(2);
		readline_loop(heredoc, ev, p);
		close(heredoc->fd);
		p->exit_status = 0;
		exit(p->exit_status);
	}
	close(heredoc->fd);
	waitpid(pid, &status, 0);
	p->exit_status = status_exec_program(status, 1);
	if (p->exit_status == 1)
		p->check_redir = 1;
}

void	last_heredocc(t_command *rt, t_redirection *hdc, t_status *p, int cmd)
{
	if (cmd == -1)
		return ;
	hdc->fd = open(hdc->file, O_RDONLY);
	if (!hdc->fd)
	{
		write(2, "minishell : ", 12);
		perror("open");
		p->check_redir = 1;
		p->exit_status = 1;
		return ;
	}
	if (dup2(hdc->fd, 0) == -1)
		dup_failed(rt, p, 2);
	close (hdc->fd);
}
