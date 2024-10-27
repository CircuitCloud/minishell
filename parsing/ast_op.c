/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykamboua <ykamboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 03:54:50 by ykamboua          #+#    #+#             */
/*   Updated: 2024/10/27 01:11:21 by ykamboua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

t_command	*create_ast_node(char *cmnd, char **args)
{
	t_command	*ast_node;

	ast_node = (t_command *)malloc(sizeof(t_command));
	if(!ast_node)
		return (NULL);
	ast_node->cmnd = cmnd;
	ast_node->args = args;
	ast_node->left = NULL;
	ast_node->right = NULL;
	return (ast_node);
}





