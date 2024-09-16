/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cahaik <cahaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 11:48:26 by cahaik            #+#    #+#             */
/*   Updated: 2024/09/16 13:07:19 by cahaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// pwd : Displays the path name of the working directory.

int pwd_(void)
{
	char *str;
	
	str = getcwd(NULL, 0);
	if (str)
	{
		printf("%s\n", str);
		free(str);
		return (0);
	}
	return (1);
}

// fach nsali should update type dyal ev f other files....

