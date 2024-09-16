/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cahaik <cahaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:26:49 by cahaik            #+#    #+#             */
/*   Updated: 2024/09/16 18:02:29 by cahaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// still not fhinished
int exit_helper(char *arg)
{
	int i;

	i = 0;
	while(arg && arg[i])
	{
		if (ft_isdigit(arg[i]) == 1 || arg[i] == '-' || arg[i] == '+'
		 || ((arg[i] == ' ') || (arg[i] >= 9 && arg[i] <= 13)))
			i++;
		else
			return (255);
	}
	return (ft_atoi(arg));
}

void exit_(char ** arg)
{
	int i;
	int size;
	int status;

	i = 0;
	size = 0;
	status = 0;
	while(arg && arg[size])
		size++;
	if (size > 1)
	{
		status = exit_helper(arg[0]);
		if (status == 255)
		{
			printf("exit\nexit: %s: numeric argument required\n", arg[0]);
			exit(status);
		}
		else
			printf("exit\nminishell: exit: too many arguments\n");
			//readline for new prompt
	}
	else if (size == 0)
	{
		printf("exit\n");
		exit(status);
		// hata men baed global variable
	}
	else
	{
		status = exit_helper(arg[0]);
		exit(status);
	}	
}

int main(int ac, char **av)
{
	char **arg;
	int i;

	arg = malloc(sizeof(char *) * (ac - 1));
	
	i = 0;
	while(i < ac - 1)
	{
		arg[i] = av[i + 1];
		// printf("%s\n", arg[i]);
		i++; 
	}
	exit_(arg);
	return (0);
}
 