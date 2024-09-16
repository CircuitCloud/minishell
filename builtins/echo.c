/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cahaik <cahaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 12:55:36 by cahaik            #+#    #+#             */
/*   Updated: 2024/09/16 12:52:28 by cahaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int check_for_n(char *arg)
{
	int i;
	int size;
	
	i = 0;
	size = ft_strlen(arg);
	while(arg && i < size)
	{
		if (arg[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}
int echo_(char **arg)
{
	int i;
	int option;
	int check;

	i = 0;
	option = 0;
	check = 0;
	while (arg && arg[i] && ft_strcmp (ft_substr(arg[i], 0, 2), "-n") == 0)
	{
		check = check_for_n(ft_substr(arg[i], 2, ft_strlen(arg[i]) - 2));
		if (check == 1)
			break;
		else if (option == 0)
			option = 1;
		i++;
	}
	while (arg && arg[i])
	{
		printf("%s", arg[i]);
		if (arg[++i])
			printf(" ");
	}
	if (option == 0)
		printf("\n");
	return (0);
}

// int main(int ac, char **av, char **env)
// {
// 	t_ev *ev;
// 	char **name;
	
// 	name = malloc(sizeof(char *) * 5);
// 	name[0] = "-nnl";
// 	// name[1]= "--n";
// 	name[1]= "-nnnnnnnnnn";
// 	name[2]= "_";
// 	name[3] = "MallocNanoZone";
// 	name[4] = "-nn";
// 	echo_(name);
// 	return (0);
// }