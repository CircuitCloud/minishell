/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cahaik <cahaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 07:04:55 by cahaik            #+#    #+#             */
/*   Updated: 2024/11/27 06:37:45 by cahaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_ev	*check_path(t_ev *ev, int *path_exist)
{
	while (ev && ev->line)
	{
		if (ft_strncmp("PATH=", ev->line, ft_strlen("PATH=")) == 0)
		{
			*path_exist = 1;
			break ;
		}
		ev = ev->next;
	}
	return (ev);
}

int	is_directory(char *cmd, int path_exist, t_status *p)
{
	struct stat	statbuf;

	if (stat(cmd, &statbuf) == 0)
	{
		if (S_ISDIR(statbuf.st_mode))
		{
			if (!ft_strchr(cmd, '/') && path_exist != 0)
				return (print_error(cmd, 2, p, 127), 2);
			else
				return (print_error(cmd, 0, p, 126), 2);
		}
	}
	return (1);
}

int	accessible(char *cmd, t_status *p)
{
	char		*slashtrim;

	slashtrim = NULL;
	if (access(cmd, F_OK) == 0)
	{
		if (access(cmd, X_OK) == 0)
			return (0);
		if (cmd && ft_strncmp(cmd, "./", 2) == 0)
			return (print_error(cmd, 3, p, 126), 2);
	}
	else
	{
		slashtrim = ft_strtrim_execution(cmd, "/");
		if (access(slashtrim, F_OK | X_OK) == 0)
			return (free(slashtrim), print_error(cmd, 5, p, 126), 2);
		free(slashtrim);
	}
	return (1);
}

void	path_exist_(char **cmd, char *line, t_status *p, int *check)
{
	int			i;
	char		**path;

	path = NULL;
	i = 0;
	if (ft_strchr(*cmd, '/'))
	{
		*check = 1;
		return ;
	}
	path = ft_split(line, '=');
	*check = search_bin(cmd, path[1], p);
	free_splited(path);
}

int	search(char **cmd, t_ev *ev, t_status *p)
{
	int		check;
	int		path_exist;

	path_exist = 0;
	if (*cmd == NULL)
		return (p->exit_status = 0, 2);
	ev = check_path(ev, &path_exist);
	if (is_directory(*cmd, path_exist, p) == 2)
		return (2);
	check = accessible(*cmd, p);
	if (check == 0)
		return (0);
	else if (check == 2)
		return (2);
	if (path_exist == 1)
	{
		path_exist_(cmd, ev->line, p, &check);
		if (check != 1)
			return (check);
	}
	return (print_error(*cmd, 1, p, 127), 1);
}
