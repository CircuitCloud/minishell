/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykamboua <ykamboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 06:18:33 by ykamboua          #+#    #+#             */
/*   Updated: 2024/11/26 10:34:24 by ykamboua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_command	*create_simple_command(char *cmnd, int args_index, t_ev *ev)
{
	t_command	*single_command;

	single_command = ft_calloc(1, sizeof(t_command));
	if (!single_command) 
		return (NULL);
	if (cmnd)
		single_command->cmnd = ft_strdup(cmnd);
	if (args_index > 0)
	{
		single_command->args = 
			ft_calloc(1, (sizeof(char *) * (args_index + 1)));
		single_command->args[args_index] = NULL;
	}
	if (ev)
		single_command->ev = ev;
	return (single_command);
}

t_redirection	*new_redir(t_redir_data *data_redir, t_ev *ev, t_status **p)
{
	t_redirection	*redir;

	redir = ft_calloc(1, sizeof(t_redirection));
	if (!redir)
		return (NULL);
	redir->hdoc_need_expand = data_redir->hdoc_expand;
	redir->type = data_redir->type;
	if (data_redir->type == HERDOC) 
	{
		redir->delimiter = ft_strdup(data_redir->delimiter);
		redir->delimiter_be4expand = ft_strdup(data_redir->raw_delimiter);
		heredocc(redir, ev, p);
	}
	else 
	{
		redir->file = ft_strdup(data_redir->file);
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
	if (ev)
		pipe_cmnd->ev = ev;
	return (pipe_cmnd);
}

void	add_redir_cmnd(t_command *command, t_redirection *redir)
{
	t_redirection	*current;

	if (!command || !redir)
		return ;
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
	t_command		*root;
	t_grp_ev_p		grp_ev_p;
	int				args_len;

	grp_ev_p.ev = ev;
	grp_ev_p.p = p;
	root = NULL;
	current = tokens;
	while (current)
	{
		if (current && current->type != PIPE)
		{
			args_len = count_args_len(tokens);
			cmd_(&current, &root, args_len, &grp_ev_p);
		}
		if (current && current->type == PIPE)
		{
			pipe_(&current, ev, &root, p);
			break ;
		}
		if (current)
			current = current->next;
	}
	return (root);
}
