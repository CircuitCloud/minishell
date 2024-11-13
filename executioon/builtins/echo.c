/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cahaik <cahaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 12:55:36 by cahaik            #+#    #+#             */
/*   Updated: 2024/11/13 03:18:26 by cahaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_for_n(char *arg)
{
	int	i;
	int	size;

	i = 0;
	size = ft_strlen(arg);
	while (arg && i < size)
	{
		if (arg[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

void	echo_(char **arg, t_status **p)
{
	int	i;
	int	option;
	int	check;

	i = 0;
	option = 0;
	check = 0;
	while (arg && arg[i] && ft_strcmp(ft_substr(arg[i], 0, 2), "-n") == 0)
	{
		check = check_for_n(ft_substr(arg[i], 2, ft_strlen(arg[i]) - 2));
		if (check == 1)
			break ;
		else if (option == 0)
			option = 1;
		i++;
	}
	while (arg && arg[i])
	{
		ft_putstr_fd(arg[i], 1);
		if (arg[++i])
			ft_putchar_fd(' ', 1);
	}
	if (option == 0)
		ft_putchar_fd('\n', 1);
	(*p)->exit_status = 0;
}
