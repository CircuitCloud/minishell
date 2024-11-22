/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cahaik <cahaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:43:47 by cahaik            #+#    #+#             */
/*   Updated: 2024/11/21 06:07:22 by cahaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	sig_handler_child(int sig)
{
	if (sig == SIGINT)
		exit(1);
}

void	signals(int c)
{
	if (c == 1)
	{
		signal(SIGINT, sig_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (c == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	else if (c == 2)
	{
		signal(SIGINT, sig_handler_child);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (c == 3)
		signal(SIGINT, SIG_IGN);
}
