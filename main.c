/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cahaik <cahaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 12:25:58 by cahaik            #+#    #+#             */
/*   Updated: 2024/11/12 07:03:11 by cahaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int gqq_signal = 0;

int main(int ac, char **av, char **env)
{
	t_command 	data;
	t_command	*tree;
	t_command	unlink_herdoc;
	t_command	*current_tree;
	t_status p;
	t_tokens *token_node;
	char *str;
	t_ev *ev;

	signals(1);
	ev = environ(env);
	str = readline("minii>");
	p.check_redir = 0;
	p.for_redir_check = 0;
	while (str)
	{
		data.cmnd = str;
		data.tokens_list = NULL;
		add_history(str);
		//data.cmnd = str;
		//data.tokens_list = NULL;
		lexer(&data);
		token_node = data.tokens_list;
		expand_env(data.tokens_list, ev);
		remove_quotes((data.tokens_list));
		tree = build_ast((data.tokens_list), ev, &p);
		current_tree = tree;
		tree->ev = ev;
		p.exit_status = 0;
		unlink_herdoc = *tree;
		// if (!tree->redir)
		// {
		// 	printf("redir");
		// 	exit(0);
		// }
		execution(tree, &p);
		last_herdoc_number(unlink_herdoc, 1);
		free(str);  
		signals(1);
		str = readline("minii>");
	}
	return (p.exit_status); // update
}