/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cahaik <cahaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 12:25:58 by cahaik            #+#    #+#             */
/*   Updated: 2024/11/23 02:22:52 by cahaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int gqq_signal = 0;

void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		gqq_signal = 1;
		rl_on_new_line();
		printf("\n");
		// rl_replace_line("", 1);
		// rl_redisplay();
	}
}

void check()
{
	system("leaks minishell");
}
int main(int ac, char **av, char **env)
{
	t_command 	data;
	t_command	*tree;
	t_command	unlink_herdoc;
	t_command	*current_tree;
	t_status p;
	t_tokens *token_node;
	char *str;
	char *trim;
	t_ev *ev;

	// atexit(check);
	(void)ac;
	(void)av;
	ev = environ(env);
	signals(1);
	str = readline("minii>");
	trim = ft_strtrim(str, " \t");
	free(str);
	str = trim;
	p.check_redir = 0;
	p.for_redir_check = 0;
	p.exit_status = 0;
	p.newfd_in = 0;
	p.newfd_out = 0;
	p.env = NULL;
	while (str)
	{
		signals(1);
		if (gqq_signal == 1)
		{
			p.exit_status = 1;
			gqq_signal = 0;
		}
		data.cmnd = str;
		data.tokens_list = NULL;
		add_history(str);
		if(!lexer(&data))
		{
			if(!syntaxe_validation(data.tokens_list))
			{
				expand_env(data.tokens_list, ev, &p);
				remove_quotes((data.tokens_list));
				tree = build_ast((data.tokens_list), ev, &p);
				tree->ev = ev;
				execution(tree, &p);
				ev =tree->ev;
				ft_free(tree, &p, 0);
			}
		}
		if(data.tokens_list)
			free_tokens_list(data.tokens_list);
		if(tree)
			free_tree(tree);
		free(str);
		signals(1);
		tree = NULL;
		str = readline("minii>");
		trim = ft_strtrim(str, " \t");
		free(str);
		str = trim;
		p.check_redir = 0;
		p.for_redir_check = 0;
		p.newfd_in = 0;
		p.newfd_out = 0;
		p.env = NULL;
	}
	clear_history();
	// system("leaks minishell");
	return (p.exit_status); // update
}
