/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykamboua <ykamboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 05:42:52 by ykamboua          #+#    #+#             */
/*   Updated: 2024/11/23 01:32:18 by ykamboua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

t_command	*create_simple_command(char *cmnd, int args_index, t_ev *ev)
{
	t_command	*single_command;

	single_command = ft_calloc(1, sizeof(t_command));
	if (!single_command) 
		return (NULL);
	if(cmnd)
		single_command->cmnd = ft_strdup(cmnd);
	if(args_index > 0)
	{
		single_command->args = ft_calloc(1, (sizeof(char *) * (args_index + 1)));
		single_command->args[args_index] = NULL;
	}
	if(ev)
		single_command->ev = ev;	
    return (single_command);
}

t_redirection	*init_redir_struct(int type, char *file, t_ev *ev, char *delimiter, t_status **p, int hdoc_expand)
{
	t_redirection	*redir;

	redir = ft_calloc(1, sizeof(t_redirection));
	if(!redir)
		return (NULL);
	redir->hdoc_need_expand = hdoc_expand;
	redir->type = type;
	if (type == HERDOC) 
	{
		redir->delimiter = ft_strdup(delimiter);
		heredocc(redir, ev, p);
    }
	else 
	{
		redir->file = ft_strdup(file);
		redir->delimiter = NULL;
    }
	return (redir);
}

t_command	*init_pipe_cmnd(t_ev *ev)
{
	t_command	*pipe_cmnd;

	pipe_cmnd = ft_calloc(1, sizeof(t_command));
	if (!pipe_cmnd)
		return (NULL);
	pipe_cmnd->cmnd = ft_strdup("|");
	pipe_cmnd->type = PIPE;
	if(ev)
		pipe_cmnd->ev = ev;	
    return (pipe_cmnd);
}

void	add_redir_cmnd(t_command *command, t_redirection *redir)
{
	t_redirection	*current;

	if(!command || !redir)
		return;
	if (!(command->redir))
		command->redir = redir;
	else
	{
		current = command->redir;
		while (current->next_redir)
			current = current->next_redir;
		current->next_redir = redir;
	}
}

t_command	*build_ast(t_tokens *tokens, t_ev *ev, t_status *p)
{
	t_tokens		*current;
	// t_tokens		*empty_current;///lcase d empty moraha cmnd
	t_tokens		*word;
	t_command		*single_command;
	t_redirection	*redir_command;
	t_command		*root;
	t_command		*last_cmnd;
	t_command		*pipe_cmnd;
	char 			*file_or_delim;
	int				i;
	int				args_len;
	int				file_delim_founded;

	file_delim_founded = 0;
	i = 0;
	root = NULL;
	current = tokens;
	while (current)
	{
		//word cmnd
		if (current && current->type != PIPE)
		{
			args_len = 0;
			word = current;
			while (word && word->type != PIPE)
			{
				if (word->type == I_RED || word->type == O_RED || word->type == APPEND || word->type == HERDOC)
					file_delim_founded++;
				if(word->type == WORD)
					args_len++;
				word= word->next;
			}
			args_len = args_len - file_delim_founded;
			// printf("leen : (%d)\n", args_len);
			if(current && current->type == WORD)
				single_command = create_simple_command(current->value, args_len, ev);
			else
				single_command = create_simple_command(NULL, args_len, ev);
			while (current && current->type == WORD)
			{
				if (current->value && ft_strcmp(current->value, "") != 0)
				{
					if (!single_command->cmnd || ft_strcmp(single_command->cmnd, "") == 0)
					{
						if(ft_strcmp(single_command->cmnd, "") == 0)
							free(single_command->cmnd);
						single_command->cmnd = ft_strdup(current->value);
					}
					single_command->args[i] = ft_strdup(current->value);
					if (!single_command->args[i])
					{
						printf("faaailed to allocate memory for args[%d]\n", i);
						// frre yawa free
					}
					i++;
				}
				current = current->next;
			}
			while (current && current->type != PIPE)
			{
				//redirection
				if (current && (current->type == I_RED || current->type == O_RED || current->type == APPEND || current->type == HERDOC))
				{
					file_or_delim = current->next ? current->next->value : NULL;
					//nzidu p awla lfunction treturni
					if (current && current->type == HERDOC)
						redir_command = init_redir_struct(current->type, NULL, ev, file_or_delim , &p, current->hdoc_expand);
					else
						redir_command = init_redir_struct(current->type, file_or_delim , ev, NULL, &p, current->hdoc_expand);
					add_redir_cmnd(single_command, redir_command);
					current = current->next->next;
					// current = current->next;
				}
				else if(current && current->type == WORD)
				{
					if(single_command && single_command->args)
					{
						if (!single_command->cmnd)
							single_command->cmnd = ft_strdup(current->value);
						single_command->args[i] = ft_strdup(current->value);
						i++;
					}
					current = current->next;
				}
				else
					break;
			}
			if (!root)
				root = single_command;
			else
				last_cmnd->right = single_command;
			last_cmnd = single_command;
		}
		if(current && current->type == PIPE)
		{
			pipe_cmnd = init_pipe_cmnd(ev);
			pipe_cmnd->left = root;
			current = current->next;
			pipe_cmnd->right = build_ast(current, ev, p);
			root = pipe_cmnd;
			break;
		}
		if (current)
			current = current->next;
	}
	return (root);
}
