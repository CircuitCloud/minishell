/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cahaik <cahaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 10:25:07 by cahaik            #+#    #+#             */
/*   Updated: 2024/09/09 12:10:44 by cahaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int search_bin(char *cmd, char *ev, char **env)
{
	int i;
	char **splited;
	char *join;
	char *joined;
	char *command[] = {cmd, NULL};

	i = 0;
	splited = ft_split(ev, ':');
	while (splited && splited[i])
	{
		if (ft_strcmp(cmd , splited[i]) == 0)
			return (printf("%s: is a directory\n", cmd), 1);
		else
		{
			if (ft_strcmp(ft_substr(cmd, 0, ft_strlen(cmd) - ft_strlen(ft_strrchr(cmd, '/'))), splited[i]) == 0)
			{
				if (access(cmd, F_OK | X_OK) == 0)
				{
					execve(cmd, command, env);
					return (0);
				}
				break ;
			}
		}
		i++;
	}
	i = 0;
	while (splited && splited[i])
	{
		join = ft_strjoin(splited[i], "/");
		joined = ft_strjoin(join, cmd);
		if (access(joined, F_OK | X_OK) == 0)
		{
			execve(joined, command, env);
				return (0);
		}
		i++;
	}
	return (printf("%s: No such file or directory\n", cmd), 1);
}

int search(char *cmd, char **ev)
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
	int i;

	i = 0;
	char *cmd = "ls";
	if (search(cmd, ev) == 1)
		return (1);
	return (0);
}