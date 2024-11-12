/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykamboua <ykamboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 12:25:58 by cahaik            #+#    #+#             */
/*   Updated: 2024/11/12 13:09:00 by ykamboua         ###   ########.fr       */
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
	char *trim;
	t_ev *ev;

	signals(1);
	ev = environ(env);
	str = readline("minii>");
	trim = ft_strtrim(str, " \t");
	free(str);
	str = trim;
	p.check_redir = 0;
	p.for_redir_check = 0;
	while (str)
	{
		data.cmnd = str;
		data.tokens_list = NULL;
		add_history(str);
		lexer(&data);
		token_node = data.tokens_list;
		// printf("3ela berra \n");
		if(!syntaxe_validation(token_node))
		{
			printf("dakheel 3lyha \n");
			expand_env(data.tokens_list, ev);
			remove_quotes((data.tokens_list));
			tree = build_ast((data.tokens_list), ev, &p);
			current_tree = tree;
			tree->ev = ev;
			p.exit_status = 0;
			unlink_herdoc = *tree;
			// execution(tree, &p);
			last_herdoc_number(unlink_herdoc, 1);
			print_ast(tree, 0);
		}
		else
			printf("syntax e4ooo4 \n");
		free(str);  
		signals(1);
		// printf("ltee7t \n");
		str = readline("minii>");
		trim = ft_strtrim(str, " \t");
		free(str);
		str = trim;
	}
	return (p.exit_status); // update
}
