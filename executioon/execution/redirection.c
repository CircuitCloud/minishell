/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cahaik <cahaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 13:26:29 by cahaik            #+#    #+#             */
/*   Updated: 2024/11/13 01:59:45 by cahaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int last_herdoc_number(t_command copy, int option)
{
	int i;

	i = 0;
	
	while(copy.redir)
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

void	redirection(t_command *root, t_status **p)
{
	int i;
	int command;
	
	i = 0;
	command = 0;
	(*p)->last_herdoc = 0;
	(*p)->for_redir_check = 2;
	(*p)->last_herdoc = last_herdoc_number(*root, 0);
	while (root && root->redir)
	{
		if (!root->cmnd)
			command = -1;
		if (root->redir->type == O_RED && out_redir(root->redir, p, command) == 1)
			return ;
		else if (root->redir->type == I_RED && in_redir(root->redir, p, command) == 1)
		{
			(*p)->check_redir = 1;
			return ;
		}
		else if (root->redir->type == APPEND && append_redir(root->redir, p, command) == 1)
			return ;
		else if (root->redir->type == HERDOC)
		{
			i++;
			if (i == (*p)->last_herdoc)
				last_heredocc(root->redir, root->redir->file, command);
		}
		root->redir = root->redir->next_redir;
	} 
}
