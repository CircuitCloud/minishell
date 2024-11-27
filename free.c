/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cahaik <cahaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 06:37:58 by cahaik            #+#    #+#             */
/*   Updated: 2024/11/27 04:38:44 by cahaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (redir->delimiter_be4expand)
			free(redir->delimiter_be4expand);
		tmp = redir;
		redir = redir->next_redir;
		free(tmp);
	}
	redir = NULL;
}

void	free_tokens_list(t_tokens *tokens)
{
	t_tokens	*next;

	while (tokens)
	{
		next = tokens->next;
		if (tokens->value)
		{
			free(tokens->value);
			tokens->value = NULL;
		}
		if (tokens->raw_delimiter)
		{
			free(tokens->raw_delimiter);
			tokens->raw_delimiter = NULL;
		}
		free(tokens);
		tokens = next;
	}
}

void	free_tree(t_command *root)
{
	int	i;

	i = 0;
	if (!root)
		return ;
	if (root->left)
		free_tree(root->left);
	if (root->right)
		free_tree(root->right);
	while (root->args && root->args[i])
	{
		free(root->args[i]);
		i++;
	}
	if (root->args)
		free(root->args);
	if (root->tokens_list)
		free_tokens_list(root->tokens_list);
	if (root->redir)
		free_redirect(root->redir);
	if (root->cmnd)
		free(root->cmnd);
	free(root);
	root = NULL;
}

void	ft_free(t_command *root, t_status *p, int i)
{
	(void)p;
	if (root)
		free_tree(root);
	if (i == 1)
		free_env(root->ev);
}
