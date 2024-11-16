/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cahaik <cahaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 07:04:55 by cahaik            #+#    #+#             */
/*   Updated: 2024/11/16 05:15:53 by cahaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	search(char **cmd, t_ev *ev, t_status **p)
{
	char		**path;
    int 		check;
	int 		path_exist;
	char		*slashtrim;
	struct stat statbuf;
	
	path_exist = 0;
	if (*cmd == NULL)
		return (2);
	while (ev && ev->line)
	{
		if (ft_strncmp("PATH=", ev->line, ft_strlen("PATH=")) == 0)
        {
			path_exist = 1;
			break;
		}
		ev = ev->next;
	}
	if (stat(*cmd, &statbuf) == 0)
	{
			if (S_ISDIR(statbuf.st_mode))
			{
				if (!ft_strchr(*cmd, '/') && path_exist != 0)
					return (print_error(*cmd, 2, p, 127), 2);
				else
					return (print_error(*cmd, 0, p, 126), 2);
			}
	}
	if (access(*cmd, F_OK | X_OK) == 0)
			return (0);
	else
	{
		slashtrim = ft_strtrim_execution(*cmd, "/");
		if (access(slashtrim, F_OK | X_OK) == 0)
			return (free(slashtrim), print_error(*cmd, 5, p, 126), 2);
		free(slashtrim);
	}
	if (path_exist == 1)
	{
		if (ft_strchr(*cmd, '/'))
			return (1);
		path = ft_split(ev->line, '=');
		check = search_bin(cmd, path[1], p);
		if (check == 0)
			return (0);
		else if (check == 2)
			return (2);
	}	
	return (1);
}
