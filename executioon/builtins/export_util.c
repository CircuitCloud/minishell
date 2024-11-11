/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cahaik <cahaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 13:45:26 by cahaik            #+#    #+#             */
/*   Updated: 2024/11/07 04:01:47 by cahaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	valide_var(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (i == 0 && ft_isalpha(arg[i]) != 1)
			return (1);
		else if (i != 0 && arg[i] == '+' && arg[i + 1] == '=')
			return (0);
		else if (i != 0 && arg[i] == '=')
			return (2);
		else if (ft_isalpha(arg[i]) != 1 && ft_isdigit(arg[i]) != 1 
			&& arg[i] != '_')
			return (1);
		i++;
	}
	return (3);
}
