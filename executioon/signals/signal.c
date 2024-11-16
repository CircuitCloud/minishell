/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cahaik <cahaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:43:47 by cahaik            #+#    #+#             */
/*   Updated: 2024/11/16 06:20:49 by cahaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		gqq_signal = 1;
		rl_on_new_line();
		printf("\n");
		rl_replace_line("", 1);
		rl_redisplay();
	}
}
void	sig_handler_child(int sig)
{
	if (sig == SIGQUIT)
		write(1, "Quit: 3\n", 8);
	else
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
		signal(SIGQUIT, sig_handler_child);
	}
	else if (c == 2)
	{
		signal(SIGINT, sig_handler_child);
		signal(SIGQUIT, SIG_IGN);
	}
	
}
