/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cahaik <cahaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 09:43:40 by cahaik            #+#    #+#             */
/*   Updated: 2024/11/12 06:55:23 by cahaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	out_redirect(t_redirection *root_redir, t_status **p)
{
	if ((*p)->newfd_out < 0)
	{
		perror("dup failed");
		(*p)->exit_status = 1;
		return ;
	}
	if (dup2(root_redir->fd, 1) == -1)
	{
		perror("dup2 failed");
		(*p)->exit_status = 1;
	}
	close(root_redir->fd);
}

void	input_redirect(t_redirection *root_redir, t_status **p)
{
	if ((*p)->newfd_in < 0)
	{
		perror("dup failed");
		(*p)->exit_status = 1;
		return ;
	}
	if (dup2(root_redir->fd, 0) == -1)
	{
		perror("dup2 failed");
		(*p)->exit_status = 1;
	}
	close(root_redir->fd);
}

int out_redir(t_redirection *root_redir, t_status **p, int command)
{
	root_redir->fd = open(root_redir->file, O_CREAT 
		| O_WRONLY | O_TRUNC, 0644);
	if (root_redir->fd == -1)
	{
		perror(root_redir->file);
		(*p)->exit_status = 1;
		return (1);
	}
	else if (command == -1)
		return (0);
	else
		out_redirect(root_redir, p);
	return (0);
}

int in_redir(t_redirection *root_redir, t_status **p, int command)
{
	root_redir->fd = open(root_redir->file, O_RDONLY, 0644);
	if (root_redir->fd == -1)
	{
		perror(root_redir->file);
		(*p)->exit_status = 1;
		return (1);
	}
	else if (command == -1)
		return (0);
	else
		input_redirect(root_redir, p);
	return (0);
}

int append_redir(t_redirection *root_redir, t_status **p, int command)
{
	root_redir->fd = open(root_redir->file, O_CREAT 
		| O_WRONLY | O_APPEND, 0644);
	if (root_redir->fd == -1)
	{
		perror(root_redir->file);
		(*p)->exit_status = 1;
		return (1);
	}
	else if (command == -1)
		return (0);
	else
		out_redirect(root_redir, p);
	return (0);
}
