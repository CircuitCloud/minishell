/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cahaik <cahaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 10:25:07 by cahaik            #+#    #+#             */
/*   Updated: 2024/11/23 06:45:57 by cahaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	only_cmd(char **cmd, char **splited)
{
	int		i;
	char	*join;
	char	*joined;

	i = 0;
	while (splited && splited[i])
	{
		join = ft_strjoin(splited[i], "/");
		joined = ft_strjoin(join, *cmd);
		if (access(joined, F_OK | X_OK) == 0)
		{
			free(*cmd);
			*cmd = ft_strdup(joined);
			return (free(join), free(joined), 0);
		}
		free(join);
		free(joined);
		i++;
	}
	return (1);
}

int	search_bin(char **cmd, char *p, t_status **p_)
{
	char	**splited;

	splited = ft_split(p, ':');
	if (only_cmd(cmd, splited) == 0)
		return (free_splited(splited), 0);
	if (ft_strchr(*cmd, '/'))
		return (free_splited(splited), 1);
	free_splited(splited);
	return (print_error(*cmd, 2, p_, 127), 2);
}

void	execute_cmd(t_status *p, t_command *root, char	*cmd)
{
	execve(cmd, root->args, p->env);
	perror(cmd);
	p->exit_status = 1;
	exit (p->exit_status);
}

void	execute_program_help(t_command *root, t_status **p)
{
	pid_t	pid;
	int		status;

	pid = 0;
	status = 0;
	(*p)->env = store_env(root, root->ev, *p);
	pid = fork();
	if (pid < 0)
		fork_failed(p);
	else if (pid == 0)
		execute_cmd(*p, root, root->cmnd);
	free_splited((*p)->env);
	original_fd(root, p);
	waitpid(pid, &status, 0);
	(*p)->exit_status = status_exec_program(status, 0);
}

int	execute_program(t_command *root, t_status **p)
{
	int		status;
	int		check;

	check = 0;
	if (!ft_strcmp(root->cmnd, "|"))
		return (execute_pipe(root, p), 0);
	if ((root->redir && (redirect_check(root, p) == 1))
		|| if_builtin(root, p) == 0)
		return (original_fd(root, p), 0);
	if (root->cmnd && !root->cmnd[0])
		return (print_error("", 2, p, 127), original_fd(root, p), 1);
	check = search(&root->cmnd, root->ev, p);
	signals(3);
	if (check == 0)
		execute_program_help(root, p);
	if (check != 0)
		original_fd(root, p);
	return (1);
}
