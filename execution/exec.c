/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cahaik <cahaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 10:25:07 by cahaik            #+#    #+#             */
/*   Updated: 2024/09/09 14:56:50 by cahaik           ###   ########.fr       */
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
int main(int ac, char **av, char **ev)
{
	pid_t pid;
	t_command p;
	char *cmd;

	(void)ac;
	(void)av;
	cmd = NULL;
	p.args = malloc(sizeof(char *) * 3);
	p.args[0] = "ls";
	p.args[1] = "-la";
	// p.args[2] = "pipe.c";
	p.ev = ev;
	if (search(&p.args[0], p.ev) == 0)
	{
		pid = fork();
		if (pid == 0)
		{
			cmd = p.args[0];
			p.args[0] = ft_strrchr(p.args[0], '/') + 1;
			execve(cmd, p.args, p.ev);
			perror("execve");
		}
		wait(&pid);
	}
	else
		return (1);
	return (0);
}
