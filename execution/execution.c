/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cahaik <cahaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 15:20:17 by cahaik            #+#    #+#             */
/*   Updated: 2024/09/15 09:17:19 by cahaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void execution(t_command *root)
{
	if (root->args[0] == "|")
		execute_pipe(root);
	else
		execute_program(root);
}


int main(int ac, char **av, char **ev)
{
	// test pipe
	t_command *root;
	t_command *left;
	t_command *right;
	t_command *root_child;
	t_command *left_right;
	t_command *right_right;

	root = create_tree(ev); 
	left = create_left(ev);
	right = create_right(ev);
	// left_right = create_right(ev);
	// right_right = create_right_child(ev);
	
	root->left = left;
	root->right = right;
	// right->left = left_right;
	// right->right = right_right;
	
	// right = create_tree(ev);
	// left_right = create_right(ev);
	// right_right = create_right_child(ev);

	// root->right->right = right;
	// root->right->right->left = left_right;
	// root->right->right->right =right_right;

	// test redirection
	execution(root);
	return (0);
}