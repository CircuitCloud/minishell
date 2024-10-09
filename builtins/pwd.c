/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cahaik <cahaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 11:48:26 by cahaik            #+#    #+#             */
/*   Updated: 2024/10/09 05:18:19 by cahaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void pwd_(t_ev *ev)
{
	char *str;
	
	str = getcwd(NULL, 0);
	if (str)
	{
		printf("%s\n", str);
		free(str);
		return ;
	}
	while (ev)
	{
		if (ft_strcmp(ev->name, "OLDPWD") == 0)
		{
			printf("%s\n", ev->value);
			return ;
		}
		ev = ev->next;
	}
}

// fach nsali should update type dyal ev f other files....