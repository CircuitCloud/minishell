/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cahaik <cahaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 06:37:58 by cahaik            #+#    #+#             */
/*   Updated: 2024/11/17 09:26:43 by cahaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_env(t_ev *ev)
{
	t_ev *tmp;

		tmp = NULL;
		if (!ev)
			return ;
		while (ev)
		{
			if (ev->line)
				free(ev->line);
			if (ev->name)
				free(ev->name);
			if (ev->value)
				free(ev->value);
			tmp = ev;
			ev = ev->next;
			free(tmp);
		}
}

void free_redirect(t_redirection *redir)
{
	t_redirection *tmp;

	tmp = NULL;
	while (redir)
	{
		if (redir->file)
			free(redir->file);
		if (redir->delimiter)
			free(redir->delimiter);
		tmp = redir;
		redir = redir->next_redir;
		free(tmp);
	}
}

void free_tree(t_command *root)
{
	int i;

	i = 0;
	if (!root)
		return;
	free_tree(root->left);
	free_tree(root->right);
	while (root->args && root->args[i])
	{
		free(root->args[i]);
		i++;
	}
	if (root->args)
		free(root->args);
	free_env(root->ev);
	free_redirect(root->redir);
	//free token ia kan raybqa f struct
	if (root->cmnd)
		free(root->cmnd);
	free(root);
}
