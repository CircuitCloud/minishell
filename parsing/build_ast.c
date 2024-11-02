/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykamboua <ykamboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 05:42:52 by ykamboua          #+#    #+#             */
/*   Updated: 2024/11/02 08:37:13 by ykamboua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

// t_command	*build_tree(t_tokens *tokens)
// {
// 	t_tokens	*current;
// 	t_command	*cmnd_node;
// 	t_command	*root;
	
// 	root = NULL;

// 	while (current)
// 	{
// 		if(current->type == WORD)
// 			cmnd_node = create_ast_node(current->value);
// 		if(!root)
// 			root = cmnd_node;
// 	}
// }


// ls - la

t_command	*create_simple_command(char *cmnd, int args_index)
{
	t_command	*single_command;

	single_command = malloc(sizeof(t_command));
	if (!single_command) 
		return (NULL);
	single_command->cmnd = ft_strdup(cmnd);
	single_command->args = malloc((sizeof(char *) * args_index) + 2);
	
	// single_command->args[args_index + 1] = NULL;
	single_command->ev = NULL;
	// single_command->tokens_list = NULL;
	single_command->redir = NULL;
	single_command->left = NULL;
	single_command->right = NULL;
	
    return (single_command);
}

t_redirection	*init_redir_struct(int type, char *file, char *delimiter, int fd)
{
	t_redirection	*redir;
	redir = malloc(sizeof(t_redirection));

	redir->type = type;
	redir->file = file;
	redir->delimiter = delimiter;
	redir->fd = fd;
	return (redir);
}

t_command	*create_redir_cmnd(char *cmnd, int type, char *file, char *delimiter, int fd)
{
	t_command	*redir_cmnd;

	redir_cmnd = malloc(sizeof(t_command));
	if (!redir_cmnd) 
		return (NULL);
	redir_cmnd->cmnd = ft_strdup(cmnd);
	redir_cmnd->args =NULL;
	redir_cmnd->ev = NULL;
	
	redir_cmnd->redir = init_redir_struct(type, file, delimiter, fd);

	redir_cmnd->left = NULL;
	redir_cmnd->right = NULL;

	return (redir_cmnd);
}

t_command	*build_ast(t_tokens *tokens)
{
	t_tokens	*current;
	t_tokens	*word;
	t_command	*single_command;
	t_command	*redir_command;
	t_command	*root;
	t_command	*last_cmnd;
	
	// char		**stored_args;
	int			i;
	int			args_len;

	root = NULL;
	i = 0;
	
	current = tokens;
	while (current)
	{
		//word cmnd
		if(current && current->type == WORD)
		{
			args_len = 0;
			word = current;
			while (word && word->type == WORD)
			{
				args_len++;
				word= word->next;
			}
			single_command = create_simple_command(current->value, args_len - 1);
			//hhh;
			while(current && current->type == WORD)
			{
				single_command->args[i] = ft_strdup(current->value);
				i++;
				current = current->next;
			}
			single_command->args[i] = NULL;
		}

		
		//redirection

		if(current && (current->type == I_RED || current->type == O_RED || current->type == APPEND || current->type == HERDOC))
		{
			redir_command = create_redir_cmnd(current->value, current->type, current->next->value, NULL, 0);
			current = current->next;
		}
		
		if (!root)
			root = single_command;
		else
			last_cmnd->right = single_command;
		last_cmnd = single_command;
		
		
		
		if(current)
			current = current->next;
	}
	return(root);
}
