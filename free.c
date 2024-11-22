/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cahaik <cahaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 06:37:58 by cahaik            #+#    #+#             */
/*   Updated: 2024/11/21 06:13:18 by cahaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_splited(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_env(t_ev *ev)
{
	t_ev	*tmp;

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

void	free_redirect(t_redirection *redir)
{
	t_redirection	*tmp;

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

void	free_tree(t_command *root)
{
	int	i;

	i = 0;
	if (!root)
		return ;
	free_tree(root->left);
	free_tree(root->right);
	while (root->args && root->args[i])
	{
		free(root->args[i]);
		i++;
	}
	if (root->args)
		free(root->args);
	free_redirect(root->redir);
	if (root->cmnd)
		free(root->cmnd);
	free(root);
}

void	ft_free(t_command *root, t_status *p, int i)
{
	free_tree(root);
	if (i == 1)
		free_env(root->ev);
	if (p->last_herdoc != 0)
		last_herdoc_number(*root, 1);
}
