/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cahaik <cahaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 13:26:29 by cahaik            #+#    #+#             */
/*   Updated: 2024/11/21 06:34:25 by cahaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	last_herdoc_number(t_command copy, int option)
{
	int	i;

	i = 0;
	while (copy.redir)
	{
		if (copy.redir && copy.redir->type == HERDOC)
		{
			i++;
			if (option == 1)
				unlink(copy.redir->file);
		}
		copy.redir = copy.redir->next_redir;
	}
	return (i);
}

int	init_herdoc_variables(t_command root, t_status **p)
{
	(*p)->last_herdoc = 0;
	(*p)->for_redir_check = 2;
	(*p)->last_herdoc = last_herdoc_number(root, 0);
	return (0);
}

int	append_redir(t_command *root, t_redirection *redir, t_status **p, int cmd)
{
	redir->fd = open(redir->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (redir->fd == -1)
	{
		write(2, "minishell : ", 12);
		perror(redir->file);
		(*p)->check_redir = 1;
		(*p)->exit_status = 1;
		return (1);
	}
	else if (cmd == -1)
		return (0);
	else
		out_redirect(root, redir, p);
	return (0);
}

void	redirection(t_command *root, t_status **p)
{
	int	i;
	int	command;

	i = 0;
	command = init_herdoc_variables(*root, p);
	while (root && root->redir)
	{
		if (!root->cmnd)
			command = -1;
		if (root->redir->type == O_RED 
			&& out_redir(root, root->redir, p, command) == 1)
			return ;
		else if (root->redir->type == I_RED 
			&& in_redir(root, root->redir, p, command) == 1)
			return ;
		else if (root->redir->type == APPEND 
			&& append_redir(root, root->redir, p, command) == 1)
			return ;
		else if (root->redir->type == HERDOC)
		{
			if (++i == (*p)->last_herdoc)
				last_heredocc(root, root->redir, p, command);
		}
		root->redir = root->redir->next_redir;
	}
}
