/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykamboua <ykamboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 05:42:52 by ykamboua          #+#    #+#             */
/*   Updated: 2024/09/30 05:43:57 by ykamboua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

t_command *build_ast(t_tokens *tokens)
{
    if (!tokens)
        return NULL;

    t_tokens *current = tokens;
    while (current)
    {
        if (current->type == 1)
        {
            t_command *node = malloc(sizeof(t_command));
            node->left = build_ast(get_tokens_before_pipe(tokens));
            node->right = build_ast(get_tokens_after_pipe(tokens));
            node->cmnd = "|";
            return node;
        }
        current = current->next;
    }
    t_command *cmd_node = malloc(sizeof(t_command));
    cmd_node->cmnd = extract_command(tokens); 
    cmd_node->args = extract_arguments(tokens);
    return cmd_node;
}
