/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cahaik <cahaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 11:48:26 by cahaik            #+#    #+#             */
/*   Updated: 2024/09/16 11:07:20 by cahaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// pwd : Displays the path name of the working directory.

int pwd_(t_ev *envir)
{
	if (!envir)
		return (1);
	while (envir)
	{
		if (ft_strcmp(envir->name, "PWD") == 0)
		{
				printf("%s\n", envir->value);
				return (0);
		}
		envir = envir->next;
	}
	write(2, "(null)\nPWD not fount\n", 23);
	return (1);
}

// fach nsali should update type dyal ev f other files....