/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cahaik <cahaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 12:25:58 by cahaik            #+#    #+#             */
/*   Updated: 2024/11/27 07:43:03 by cahaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	g_signal = 0;

void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = 1;
		rl_on_new_line();
		printf("\n");
		rl_replace_line("", 1);
		rl_redisplay();
	}
}

void	init_p(t_status *p, int flag)
{
	if (flag == 0)
	{
		p->check_redir = 0;
		p->for_redir_check = 0;
		p->newfd_in = 0;
		p->newfd_out = 0;
		p->env = NULL;
	}
	else
	{
		if (g_signal == 1)
		{
			p->exit_status = 1;
			g_signal = 0;
		}
	}
}

void	main_helper(t_command *data, t_status *p, t_ev **ev)
{
	t_command	*tree;

	if (!lexer(data))
	{
		if (!syntaxe_validation(data->tokens_list, p))
		{
			expand_env(data->tokens_list, *ev, p);
			remove_quotes((data->tokens_list));
			tree = build_ast((data->tokens_list), *ev, p);
			tree->ev = (*ev);
			execute_program(tree, p);
			(*ev) = tree->ev;
			if (data->tokens_list)
				free_tokens_list(data->tokens_list);
			if (tree)
				ft_free(tree, p, 0);
			tree = NULL;
		}
		else
		{
			if (data->tokens_list)
				free_tokens_list(data->tokens_list);
		}
	}
}

char	*readline_handler(t_status *p)
{
	char	*str;
	char	*trim;

	signals(1);
	str = readline("minii> ");
	trim = ft_strtrim(str, " \t");
	free(str);
	str = trim;
	init_p(p, 0);
	return (str);
}

int	main(int ac, char **av, char **env)
{
	t_command	data;
	t_status	p;
	t_grp_ev_p	evp;

	(void)ac;
	(void)av;
	evp.ev = environ(env);
	evp.str = readline_handler(&p);
	p.exit_status = 0;
	while (evp.str)
	{
		init_p(&p, 1);
		data.cmnd = evp.str;
		data.tokens_list = NULL;
		add_history(evp.str);
		main_helper(&data, &p, &evp.ev);
		free(evp.str);
		evp.str = readline_handler(&p);
	}
	return (free_env(evp.ev), clear_history(), p.exit_status);
}
