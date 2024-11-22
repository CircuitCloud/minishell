/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cahaik <cahaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 06:01:14 by cahaik            #+#    #+#             */
/*   Updated: 2024/11/21 06:03:35 by cahaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	exit_(t_command *root, char **arg, t_status **p)
{
	int	err;
	int	size;

	err = 0;
	size = 0;
	while (arg && arg[size])
		size++;
	if (size > 1)
		lot_of_args(root, arg, p);
	else
	{
		if (size == 0 || ft_strcmp(arg[0], "--") == 0)
		{
			printf("exit\n");
			ft_free(root, *p, 1);
			exit((*p)->exit_status);
		}
		(*p)->exit_status = exit_helper(arg[0], &err);
		if (err == -1)
			print_error(arg[0], 4, p, -1);
		else
			printf("exit\n");
		ft_free(root, *p, 1);
		exit((*p)->exit_status); 
	}
}
