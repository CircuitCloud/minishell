/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_op2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cahaik <cahaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:00:40 by ykamboua          #+#    #+#             */
/*   Updated: 2024/11/27 00:50:53 by cahaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redir_2(t_tokens **current, t_command *cmd, t_ev *ev, t_status *p)
{
	char			*file_or_delim;
	t_redir_data	data_redir;
	t_redirection	*redir_command;

	file_or_delim = NULL;
	data_redir.type = (*current)->type;
	data_redir.raw_delimiter = (*current)->raw_delimiter;
	data_redir.hdoc_expand = (*current)->hdoc_expand;
	if ((*current)->next)
		file_or_delim = (*current)->next->value;
	if ((*current) && (*current)->type == HERDOC)
	{
		data_redir.file = NULL;
		data_redir.delimiter = file_or_delim;
	}
	else
	{
		data_redir.file = file_or_delim;
		data_redir.delimiter = NULL;
	}
	redir_command = new_redir(&data_redir, ev, p);
	add_redir_cmnd(cmd, redir_command);
	(*current) = (*current)->next->next;
}

void	redir_(t_tokens **current, t_command *cmd, t_grp_ev_p *ev_p, int *i)
{
	while ((*current) && (*current)->type != PIPE)
	{
		if ((*current) && ((*current)->type == I_RED 
				|| (*current)->type == O_RED || (*current)->type == APPEND 
				|| (*current)->type == HERDOC))
			redir_2(current, cmd, ev_p->ev, ev_p->p);
		else if ((*current) && (*current)->type == WORD)
		{
			if (cmd && cmd->args)
			{
				if (!cmd->cmnd)
					cmd->cmnd = ft_strdup((*current)->value);
				cmd->args[*i] = ft_strdup((*current)->value);
				(*i)++;
			}
			(*current) = (*current)->next;
		}
		else
			break ;
	}
}

void	pipe_(t_tokens **current, t_ev *ev, t_command **root, t_status *p)
{
	t_command		*pipe_cmnd;

	pipe_cmnd = init_pipe_cmnd(ev);
	pipe_cmnd->left = *root;
	(*current) = (*current)->next;
	pipe_cmnd->right = build_ast((*current), ev, p);
	*root = pipe_cmnd;
}
