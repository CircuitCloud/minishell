/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cahaik <cahaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 12:25:58 by cahaik            #+#    #+#             */
/*   Updated: 2024/11/07 05:41:57 by cahaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int gqq_signal = 0;
// t_command *create_tree(t_ev *ev)
// {
// 	t_command *node;
	
// 	node = malloc(sizeof(t_command));
// 	if (!node)
// 		return (NULL);
// 	node->args = malloc(sizeof(char *) * 2);
// 	node->args[0] = "|";
// 	node->args[1] = NULL;
// 	node->redir = NULL;
// 	node->cmnd = NULL;
// 	node->ev = ev;
// 	node->left = NULL;
// 	node->right = NULL;
// 	return (node);
// }

// t_redirection *create_redir(char *arg)
// {	
// 	t_redirection *node;

// 	node = malloc(sizeof(t_redirection));

// 	node->file = arg;
// 	node->type = INPUT_RED;
// 	node->next_redir = NULL;
// 	return (node);
// }

// t_command *create_left(t_ev *ev)
// {
// 	t_command *node;
	
// 	node = malloc(sizeof(t_command));
// 	if (!node)
// 		return (NULL);
// 	node->args = malloc(sizeof(char *) * 3);
// 	node->args[0] = "ls";
// 	node->args[1] = "-la";
// 	node->args[2] = NULL;
// 	node->cmnd = NULL;
// 	node->redir = create_redir("test1");
// 	node->redir->next_redir = create_redir("test2");
// 	node->redir->next_redir->next_redir = create_redir("test3");
// 	node->ev = ev;
// 	node->left = NULL;
// 	node->right = NULL;
// 	return (node);
// }

// t_command *create_right(t_ev *ev)
// {
// 	t_command *node;
	
// 	node = malloc(sizeof(t_command));
// 	if (!node)
// 		return (NULL);
// 	node->args = malloc(sizeof(char *) * 2);
// 	node->args[0] = "yes";
// 	node->args[1] = NULL;
// 	node->redir = NULL;
// 	node->cmnd = NULL;
// 	node->ev = ev;
// 	node->left = NULL;
// 	node->right = NULL;
// 	return (node);
// }

// // t_command *create_right_child(char **env)
// // {
// // 	t_command *node;
	
// // 	node = malloc(sizeof(t_command));
// // 	if (!node)
// // 		return (NULL);
// // 	node->args = malloc(sizeof(char *) * 3);
// // 	node->args[0] = "grep";
// // 	node->args[1] = "root";
// // 	node->args[2] = NULL;
// // 	node->ev = env;
// // 	node->left = NULL;
// // 	node->right = NULL;
// // 	return (node);
// // }
// int main(int ac, char **av, char **env)
// {
// 	(void)av;
// 	(void)ac;
// 	// test pipe
// 	t_command *root;
// 	t_command *left;
// 	t_command *right;
// 	t_status p;
// 	t_ev *ev;

// 	p.exit_status = 0;
// 	signals(1);
// 	// t_command *root_child;
// 	// t_command *left_right;
// 	// t_command *right_right;
// 	ev = environ(env);
// 	root = create_tree(ev); 
// 	left = create_left(ev);
// 	right = create_right(ev);
// 	root->left = left;
// 	root->right = right;
	
// 	execution(root, &p);
// 	return (p.exit_status);
// }

int main(int ac, char **av, char **env)
{
	t_command 	data;
	t_command	*tree;
	t_command	*current_tree;
	t_status p;
	
	t_tokens *token_node;
	char *str;
	t_ev *ev;

	// ev = environ(env);
	ev = environ(env);
	str = readline("minii>");
	while (str)
	{
		add_history(str);
		data.cmnd = str;
		data.tokens_list = NULL;
		lexer(&data);
		token_node = data.tokens_list;
		expand_env(data.tokens_list);
		remove_quotes((data.tokens_list));
		tree = build_ast(data.tokens_list);
		// printf("%s\n",tree->cmnd);
		// int i = 0;
		current_tree = tree;
		tree->ev = ev;
		// env_(ev,&p);
		p.exit_status = 0;
		p.check_redir = 0;
		// printf("REDIR");
		execution(tree, &p);
		// while (current_tree->args[i])
		// {
		// 	printf("%s\n", current_tree->args[i]);
		// 	i++;
		// }
		// printf("hna\n");

		// print_ast(tree, 0);
		// while (tree)
		// {
		// 	if(tree->left)
		// 		printf("left : %s\n", tree->left->cmnd);
		// 	if(tree->right)
		// 		printf("right : %s\n", tree->right->cmnd);
		// 	tree = tree->left;
		// }
		// while (token_node) 
		// {
		// 	printf("Token : (%s)\n", token_node->value);
		// 	// printf("type : (%d)\n", token_node->type);
		// 	// printf("Token : (%d)\n", token_node->type);
		// 	token_node = token_node->next;
		// }
		free(str);  
		str = readline("minii>");
	}
	return 0;
}