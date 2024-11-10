/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykamboua <ykamboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 05:42:52 by ykamboua          #+#    #+#             */
/*   Updated: 2024/11/10 05:59:10 by ykamboua         ###   ########.fr       */
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
//---------------------------------------------------------___________________




// t_command	*create_simple_command(char *cmnd, int args_index)
// {
// 	t_command	*single_command;

// 	single_command = malloc(sizeof(t_command));
// 	if (!single_command) 
// 		return (NULL);
// 	single_command->cmnd = ft_strdup(cmnd);
// 	single_command->args = malloc((sizeof(char *) * args_index) + 2);
// 	// single_command->args[args_index + 1] = NULL;
// 	single_command->ev = NULL;
// 	// single_command->tokens_list = NULL;
// 	single_command->redir = NULL;
// 	single_command->left = NULL;
// 	single_command->right = NULL;
	
//     return (single_command);
// }

// t_redirection	*init_redir_struct(int type, char *file, char *delimiter, int fd)
// {
// 	t_redirection	*redir;
// 	redir = malloc(sizeof(t_redirection));

// 	redir->type = type;
// 	// if()

// 	if (type == HERDOC) 
// 	{
// 		redir->delimiter = ft_strdup(delimiter);
// 		redir->file = NULL;
//     }
// 	else 
// 	{
// 		redir->file = ft_strdup(file);
// 		redir->delimiter = NULL;
//     }
// 	// redir->file =  file ? ft_strdup(file) : NULL;
// 	// redir->delimiter = delimiter ? ft_strdup(delimiter) : NULL;
// 	redir->fd = fd;
// 	redir->next_redir= NULL;
// 	return (redir);
// }


// t_command	*init_pipe_cmnd()
// {
// 	t_command	*pipe_cmnd;

// 	pipe_cmnd = malloc(sizeof(t_command));
// 	if (!pipe_cmnd)
// 		return (NULL);
// 	pipe_cmnd->cmnd = ft_strdup("|");
// 	pipe_cmnd->args = NULL;
// 	pipe_cmnd->type = PIPE;
// 	// single_command->args[args_index + 1] = NULL;
// 	pipe_cmnd->ev = NULL;
// 	// single_command->tokens_list = NULL;
// 	pipe_cmnd->redir = NULL;
// 	pipe_cmnd->left = NULL;
// 	pipe_cmnd->right = NULL;
	
//     return (pipe_cmnd);
// }

// // t_command	*add_redir_cmnd(char *cmnd, int type, char *file, char *delimiter, int fd)
// // {
// // 	t_command	*redir_cmnd;

// // 	redir_cmnd = malloc(sizeof(t_command));
// // 	if (!redir_cmnd) 
// // 		return (NULL);
// // 	redir_cmnd->cmnd = ft_strdup(cmnd);
// // 	redir_cmnd->args =NULL;
// // 	redir_cmnd->ev = NULL;
	
// // 	redir_cmnd->redir = init_redir_struct(type, file, delimiter, fd);

// // 	redir_cmnd->left = NULL;
// // 	redir_cmnd->right = NULL;

// // 	return (redir_cmnd);
// // }

// void	add_redir_cmnd(t_command *command, t_redirection *redir)
// {
// 	if (!(command->redir))
// 		command->redir = redir;
// 	else
// 	{
// 		t_redirection	*current;
// 		current = command->redir;
// 		while (current->next_redir)
// 		{
// 			current = current->next_redir;
// 		}
// 		current->next_redir = redir;
// 	}
// }

// t_command	*build_ast(t_tokens *tokens)
// {
// 	t_tokens	*current;
// 	t_tokens	*word;
// 	t_command	*single_command;
// 	t_redirection	*redir_command;
// 	t_command	*root;
// 	t_command	*last_cmnd;
// 	char *file_or_delim;

// 	// char		**stored_args;
// 	int			i;
// 	int			args_len;

// 	root = NULL;
// 	i = 0;
	
// 	current = tokens;
// 	while (current)
// 	{
// 		//word cmnd
// 		if (current && current->type == WORD)
// 		{
// 			args_len = 0;
// 			word = current;
// 			while (word && word->type != PIPE)
// 			{
// 				if(word->type == WORD)
// 					args_len++;
// 				word= word->next;
// 			}
// 			single_command = create_simple_command(current->value, args_len);
// 			//hhh;
// 			while(current && current->type == WORD)
// 			{
// 				single_command->args[i] = ft_strdup(current->value);
// 				i++;
// 				current = current->next;
// 			}
// 			single_command->args[i] = NULL;
// 			if (!root)
// 				root = single_command;
// 			else
// 			{
// 				last_cmnd->right = single_command;
// 				// printf("linnnnnnking %s -> right to %s\n", last_cmnd->cmnd, single_command->cmnd);
// 			}
// 			last_cmnd = single_command;
// 		}
// 		//redirection
// 			if (current && (current->type == I_RED || current->type == O_RED || current->type == APPEND || current->type == HERDOC))
// 			{
// 				file_or_delim = current->next ? current->next->value : NULL;
// 				if (current && current->type == HERDOC)
// 					redir_command = init_redir_struct(current->type, NULL, file_or_delim , 0);
// 				else
// 					redir_command = init_redir_struct(current->type, file_or_delim , NULL, 0);
// 				// redir_command = init_redir_struct(current->type, current->next->value,current->next->value, 0);
// 				add_redir_cmnd(last_cmnd, redir_command);
// 				current = current->next; //bash nskiiper redir
// 				current = current->next;// bash nskiper deli/file
				
// 				//args moora rediiiirec-----------------------------------------------------------
// 				while(current && current->type == WORD)
// 				{
// 					single_command->args[i] = ft_strdup(current->value);
// 					// printf("%s\n",current->value);
// 					i++;
// 					current = current->next;
// 				}
// 				//------------------------------------------------------------------------------------
// 			}


		
// 		if(current && current->type == PIPE)
// 		{
// 			t_command	*pipe_cmnd;
// 			pipe_cmnd = init_pipe_cmnd();
			
// 			pipe_cmnd->left = root;
// 			current = current->next;
// 			pipe_cmnd->right = build_ast(current);
// 			root = pipe_cmnd;
// 			break;
// 		}
// 		if (current)
// 			current = current->next;
// 	}
// 	return (root);
// }


//______________________________________________________________________




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
	// if()

	if (type == HERDOC) 
	{
		redir->delimiter = ft_strdup(delimiter);
		redir->file = NULL;
    }
	else 
	{
		redir->file = ft_strdup(file);
		redir->delimiter = NULL;
    }
	// redir->file =  file ? ft_strdup(file) : NULL;
	// redir->delimiter = delimiter ? ft_strdup(delimiter) : NULL;
	redir->fd = fd;
	redir->next_redir= NULL;
	return (redir);
}


t_command	*init_pipe_cmnd()
{
	t_command	*pipe_cmnd;

	pipe_cmnd = malloc(sizeof(t_command));
	if (!pipe_cmnd)
		return (NULL);
	pipe_cmnd->cmnd = ft_strdup("|");
	pipe_cmnd->args = NULL;
	pipe_cmnd->type = PIPE;
	// single_command->args[args_index + 1] = NULL;
	pipe_cmnd->ev = NULL;
	// single_command->tokens_list = NULL;
	pipe_cmnd->redir = NULL;
	pipe_cmnd->left = NULL;
	pipe_cmnd->right = NULL;
	
    return (pipe_cmnd);
}

// t_command	*add_redir_cmnd(char *cmnd, int type, char *file, char *delimiter, int fd)
// {
// 	t_command	*redir_cmnd;

// 	redir_cmnd = malloc(sizeof(t_command));
// 	if (!redir_cmnd) 
// 		return (NULL);
// 	redir_cmnd->cmnd = ft_strdup(cmnd);
// 	redir_cmnd->args =NULL;
// 	redir_cmnd->ev = NULL;
	
// 	redir_cmnd->redir = init_redir_struct(type, file, delimiter, fd);

// 	redir_cmnd->left = NULL;
// 	redir_cmnd->right = NULL;

// 	return (redir_cmnd);
// }

void	add_redir_cmnd(t_command *command, t_redirection *redir)
{
	if (!(command->redir))
		command->redir = redir;
	else
	{
		t_redirection	*current;
		current = command->redir;
		while (current->next_redir)
		{
			current = current->next_redir;
		}
		current->next_redir = redir;
	}
}

t_command	*build_ast(t_tokens *tokens)
{
	t_tokens	*current;
	t_tokens	*word;
	t_command	*single_command;
	t_redirection	*redir_command;
	t_command	*root;
	t_command	*last_cmnd;
	char *file_or_delim;

	// char		**stored_args;
	int			i;
	int			args_len;

	root = NULL;
	i = 0;
	
	current = tokens;
	while (current)
	{
		//word cmnd
		if (current && current->type == WORD)
		{
			args_len = 0;
			word = current;
			while (word && word->type != PIPE)
			{
				if(word->type == WORD)
					args_len++;
				word= word->next;
			}
			single_command = create_simple_command(current->value, args_len);
			//hhh;
			while(current && current->type == WORD)
			{
				single_command->args[i] = ft_strdup(current->value);
				i++;
				current = current->next;
			}
			
			while (current && current->type != PIPE)
			{
				//redirection
				if (current && (current->type == I_RED || current->type == O_RED || current->type == APPEND || current->type == HERDOC))
				{
					file_or_delim = current->next ? current->next->value : NULL;
					if (current && current->type == HERDOC)
						redir_command = init_redir_struct(current->type, NULL, file_or_delim , 0);
					else
						redir_command = init_redir_struct(current->type, file_or_delim , NULL, 0);
					// redir_command = init_redir_struct(current->type, current->next->value,current->next->value, 0);
					add_redir_cmnd(single_command, redir_command);
					current = current->next; //bash nskiiper redir
					current = current->next;// bash nskiper deli/file
				}
				//args moora rediiiirec-----------------------------------------------------------
				else if(current && current->type == WORD)
				{
					single_command->args[i] = ft_strdup(current->value);
					// printf("%s\n",current->value);
					i++;
					current = current->next;
				}
					//------------------------------------------------------------------------------------
				else
					break;/////
			}
			single_command->args[i] = NULL;
			if (!root)
				root = single_command;
			else
			{
				last_cmnd->right = single_command;
				// printf("linnnnnnking %s -> right to %s\n", last_cmnd->cmnd, single_command->cmnd);
			}
			last_cmnd = single_command;
		}

		if(current && current->type == PIPE)
		{
			t_command	*pipe_cmnd;
			pipe_cmnd = init_pipe_cmnd();
			
			pipe_cmnd->left = root;
			current = current->next;
			pipe_cmnd->right = build_ast(current);
			root = pipe_cmnd;
			break;
		}
		if (current)
			current = current->next;
	}
	return (root);
}
