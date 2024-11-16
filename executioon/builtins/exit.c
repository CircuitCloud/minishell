/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cahaik <cahaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:26:49 by cahaik            #+#    #+#             */
/*   Updated: 2024/11/16 07:51:42 by cahaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	_spaces(char *str, int *sign, int *i, int func)
{
	while ((str[*i] == ' ') || (str[*i] >= 9 && str[*i] <= 13))
		(*i)++;
	if (func != 0)
	{
		if (!str[*i] || str[*i] == '-' || str[*i] == '+')
		{
			if (!str[*i])
				return (1);
			else if (str[*i] == '-')
				*sign = -1;
			(*i)++;
		}
	}
	return (0);
}

long long	atoi_exit(char *str, int *err)
{
	int		i;
	int			sign;
	long long	cpy;
	long long	number;

	i = 0;
	cpy = 0;
	sign = 1;
	number = 0;
	if (_spaces(str, &sign, &i, 1) == 1)
		return (*err = -1, 255);
	while (str[i] >= '0' && str[i] <= '9')
	{
		cpy = number;
		number = (number * 10) + sign * (str[i] - '0');
		if ((cpy > number && sign > 0) || (cpy < number && sign < 0))
			return (*err = -1, 255);
		i++;
	}
	_spaces(str, &sign, &i, 0);
	if (i != ft_strlen(str) && str[i] != '\0')
		return (*err = -1, 255);
	return (number);
}

int	exit_helper(char *arg, int *err)
{
	long long	number;

	number = atoi_exit(arg, err);
	return (number);
}

void	exit_many_args(t_status **p, int err, char *arg)
{
	if (err == -1)
	{
		print_error(arg, 4, p, -1);
		exit((*p)->exit_status);
	}
	write(2, "exit\nminishell: exit: too many arguments\n", 42);
	(*p)->exit_status = 1;
}

void lot_of_args(char **arg , t_status **p)
{
	int err;

	err = 0;
	(*p)->exit_status = exit_helper(arg[0], &err);
	exit_many_args(p, err, arg[0]);
}

void	exit_(char **arg, t_status **p)
{
	int	err;
	int	size;

	err = 0;
	size = 0;
	while (arg && arg[size])
		size++;
	if (size > 1)
		lot_of_args(arg , p);
	else
	{
		if (size == 0 || ft_strcmp(arg[0], "--") == 0)
		{
			printf("exit\n");
			exit((*p)->exit_status);
		}
		(*p)->exit_status = exit_helper(arg[0], &err);
		if (err == -1)
			print_error(arg[0], 4, p, -1);
		else
			printf("exit\n");
		exit((*p)->exit_status); 
	}
}
