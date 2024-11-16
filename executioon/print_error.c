/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cahaik <cahaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 13:43:58 by cahaik            #+#    #+#             */
/*   Updated: 2024/11/16 08:14:17 by cahaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void print_error(char *err, int type, t_status **p_, int exit_s)
{
	char *p;

	p = NULL;
	if (type != 3 || type != 4)
		write(2, "minishell: ", 11);
	if (type == 0)
		p = ft_strjoin(err, " : is a directory\n");
	else if (type == 1)
		p = ft_strjoin(err, " : No such file or directory\n");
	else if (type == 2)
		p = ft_strjoin(err, " : command not found\n");
	else if (type == 4)
	{
		write (2, "exit\nminishell: exit: ", 23);
		p = ft_strjoin(err, ": numeric argument required\n");
	}
	else if (type == 5)
		p = ft_strjoin(err, ": Not a directory\n");
	write (2, p, ft_strlen(p));
	if (exit_s != -1)
		(*p_)->exit_status = exit_s;
	free(p);
}

void perror_(char *err, t_status **p)
{
	write (2, "minishell: cd: ", 15);
	perror(err);
	(*p)->exit_status = 1;
}