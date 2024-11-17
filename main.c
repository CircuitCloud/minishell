/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykamboua <ykamboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 12:25:58 by cahaik            #+#    #+#             */
/*   Updated: 2024/11/17 22:47:27 by ykamboua         ###   ########.fr       */
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
		rl_replace_line("", 1);
		rl_redisplay();
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
		lexer(&data);
		token_node = data.tokens_list;
		// printf("3ela berra \n");
		if(!syntaxe_validation(token_node))
		{
			// printf("dakheel 3lyha \n");
			expand_env(data.tokens_list, ev, &p);
			remove_quotes((data.tokens_list));
			tree = build_ast((data.tokens_list), ev, &p);
			// if (!tree->cmnd && tree->args && tree->args[0])
			// 	tree->cmnd = ft_strdup(tree->args[0]);
			current_tree = tree;
			tree->ev = ev;
			unlink_herdoc = *tree;
			execution(tree, &p);
			last_herdoc_number(unlink_herdoc, 1);
			// print_ast(tree, 0);
		}
		
		free(str);  
		// printf("ltee7t \n");
		signals(1);
		str = readline("minii>");
		trim = ft_strtrim(str, " \t");
		free(str);
		str = trim;
	}
	return (p.exit_status); // update
}
