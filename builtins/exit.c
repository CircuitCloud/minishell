/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cahaik <cahaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:26:49 by cahaik            #+#    #+#             */
/*   Updated: 2024/10/09 03:13:31 by cahaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

long long atoi_exit(char *str, int *err)
{
	size_t	i;
	int		sign;
	long long	cpy;
	long long number;

	i = 0;
	cpy = 0;
	sign = 1;
	number = 0;
	while ((str[i] == ' ') || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (!str[i] || str[i] == '-' || str[i] == '+')
	{
		if (!str[i])
			return (*err = -1, 255);
		else if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		cpy = number;
		number = (number * 10) + sign * (str[i] - '0');
		if ((cpy > number && sign > 0) || (cpy < number && sign < 0))
			return (*err = -1, 255);
		i++;
	}
	while ((str[i] == ' ') || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (i != ft_strlen(str) && str[i] != '\0')
		return (*err = -1, 255);
	return (number);
}

int exit_helper(char *arg, int *err)
{
	long long number;
	
	number = atoi_exit(arg, err);
	return (number);
}

void exit_(char ** arg)
{
	int err;
	int size;
	int status;

	err = 0;
	size = 0;
	status = 0;
	while(arg && arg[size])
		size++;
	if (size > 1)
	{
		status = exit_helper(arg[0], &err);
		if (err == -1)
		{
			printf("exit\nexit: %s: numeric argument required\n", arg[0]);
			exit(status);
		}
		else
			printf("exit\nminishell: exit: too many arguments\n");
			//status = 1; // to fix it in global var
			//readline for new prompt
	}
	else
	{
		printf("exit\n");
		if (size == 0 || ft_strcmp(arg[0], "--") == 0)
			exit(status); // global variable status
		status = exit_helper(arg[0], &err);
		if (err == -1)
			printf("minishell: exit: %s: numeric argument required\n", arg[0]);
		exit(status);
	}	
}

// int main(int ac, char **av)
// {
// 	char **arg;
// 	int i;

// 	arg = malloc(sizeof(char *) * (ac - 1));
	
// 	i = 0;
// 	while(i < ac - 1)
// 	{
// 		arg[i] = av[i + 1];
// 		// printf("%s\n", arg[i]);
// 		i++; 
// 	}
// 	exit_(arg);
// 	return (0);
// }
 