/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cahaik <cahaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 10:25:07 by cahaik            #+#    #+#             */
/*   Updated: 2024/09/13 21:21:53 by cahaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int only_cmd(char **cmd, char **splited)
{
	int i;
	char *join;
	char *joined;
	
	i = 0;
	while (splited && splited[i])
	{
		join = ft_strjoin(splited[i], "/");
		joined = ft_strjoin(join, *cmd);
		if (access(joined, F_OK | X_OK) == 0)
		{
			*cmd = ft_strdup(joined);
			return (free(join), free(joined), 0);
		}
		free(join);
		free(joined);
		i++;
	}
	return (1);
}

int search_bin(char **cmd, char *ev, char **env)
{
	int i;
	char **splited;

	i = 0;
	splited = ft_split(ev, ':');
	while (splited && splited[i])
	{
		if (ft_strcmp(*cmd , splited[i]) == 0)
			return (printf("%s: is a directory\n", *cmd), 1);
		else
		{
			if (ft_strcmp(ft_substr(*cmd, 0, 
				ft_strlen(*cmd) - ft_strlen(ft_strrchr(*cmd, '/'))), splited[i]) == 0 
					&& access(*cmd, F_OK | X_OK) == 0)
					return (0);
		}
		i++;
	}
	if (ft_strchr(*cmd, '/'))
	return (printf("%s: No such file or directory\n", *cmd), 1);
	if (only_cmd(cmd, splited) == 0)
		return (0);
	return (printf("%s: command not found\n", *cmd), 1);
}

int search(char **cmd, char **ev)
{
	int i;
	char **path;

	i = 0;
	while (ev && ev[i])
	{
		if (ft_strncmp("PATH=", ev[i], ft_strlen("PATH=")) == 0)
		{
			path = ft_split(ev[i], '=');
				if (search_bin(cmd, path[1], ev) == 0)
					return (0);
		}
		i++;
	}
	return (1);
}

void execute_program(t_command *root)
{
	pid_t pid;
	char *cmd;
	
	cmd = NULL;
	if (!ft_strcmp(root->args[0], "|"))
	{
		execute_pipe(root);
		return ;
	}
	else if (search(&root->args[0], root->ev) == 0)
	{
		pid = fork();
		if (pid == 0)
		{
			cmd = root->args[0];
			root->args[0] = ft_strrchr(root->args[0], '/') + 1;
			execve(cmd, root->args, root->ev);
			perror("execve");
			exit (1);
		}
		waitpid(pid, NULL, 0);
	}
}