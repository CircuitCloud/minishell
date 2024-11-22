/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cahaik <cahaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 12:55:36 by cahaik            #+#    #+#             */
/*   Updated: 2024/11/21 05:59:51 by cahaik           ###   ########.fr       */
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

int	echo_help(char **arg, int *option)
{
	int		i;
	int		check;
	char	*sub;

	i = 0;
	sub = NULL;
	check = 0;
	while (arg && arg[i])
	{
		sub = ft_substr(arg[i], 0, 2);
		if (ft_strcmp(sub, "-n") != 0)
			return (free(sub), i);
		free(sub);
		sub = ft_substr(arg[i], 2, ft_strlen(arg[i]) - 2);
		check = check_for_n(sub);
		if (check == 1)
			return (free(sub), i);
		else if ((*option) == 0)
			(*option) = 1;
		i++;
		free(sub);
	}
	return (i);
}

void	echo_(char **arg, t_status **p)
{
	int	i;
	int	option;

	i = 0;
	option = 0;
	i = echo_help(arg, &option);
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
