/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cahaik <cahaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 21:54:21 by cahaik            #+#    #+#             */
/*   Updated: 2024/11/12 06:35:04 by cahaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void heredocc(t_redirection *heredoc, t_status **p)
{
	static int i;
	
	
	heredoc->file = ft_strjoin("/tmp/heredocs", ft_itoa(++i));
	heredoc->fd = open(heredoc->file, O_CREAT | O_WRONLY, 0644);
	if (heredoc->fd < 0)
	{
		perror("open");
		(*p)->exit_status = 1;
		exit ((*p)->exit_status);
	}
	all_heredocs(heredoc, p);
}

void all_heredocs(t_redirection *heredoc, t_status **p)
{
	char *input;
	pid_t pid;
	int status;
	
	pid = fork();
	status = 0;
	if (pid < 0)
	{
		perror("fork");
		(*p)->exit_status = 1;
		exit((*p)->exit_status);
	}
	else if (pid == 0)
	{
		signals(2);
		while (1)
		{
			input = readline(">");
			if (!heredoc->file)
				break ; //EOF OR ERROR
			if (ft_strcmp(input, heredoc->delimiter) == 0)
			{
				free(input);
				break;
			}
			write(heredoc->fd, input, ft_strlen(input));
			write(heredoc->fd, "\n", 1);
			free(input);
		}
		close(heredoc->fd);
		exit(0);
	}
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
		(*p)->exit_status = WTERMSIG(status);
	else
		(*p)->exit_status = WEXITSTATUS(status);
	if ((*p)->exit_status == 1)
		(*p)->check_redir = 1;
}

void last_heredocc(t_redirection *heredoc, char *name, int command)
{
	if (command == -1)
		return ;
	heredoc->fd = open(name, O_RDONLY);
	dup2(heredoc->fd, 0);
	close (heredoc->fd);
}
// unlink heredoc's file when i finish working
// should fork + signal + for a lot of heredos
// free kulxi