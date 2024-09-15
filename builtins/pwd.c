/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cahaik <cahaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 11:48:26 by cahaik            #+#    #+#             */
/*   Updated: 2024/09/15 12:15:36 by cahaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// pwd : Displays the path name of the working directory.

int main(int ac, char **av, char **ev)
{
	t_ev *envir;
	
	envir = environ(ev);
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
	write(2, "PWD not fount\n", 15);
	return (1);
}

// fach nsali should update type dyal ev f other files....