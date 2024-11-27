/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cahaik <cahaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 09:43:40 by cahaik            #+#    #+#             */
/*   Updated: 2024/11/27 04:35:36 by cahaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	dup_failed(t_command *root, t_status *p, int c)
{
	(void)root;
	write (2, "minishell : ", 12);
	if (c == 2)
		perror("dup2");
	else
		perror("dup failed");
	p->exit_status = 1;
	exit(p->exit_status);
}

void	out_redirect(t_command *root, t_redirection *root_redir, t_status *p)
{
	if (p->newfd_out < 0)
		dup_failed(root, p, 0);
	if (dup2(root_redir->fd, 1) == -1)
		dup_failed(root, p, 2);
	close(root_redir->fd);
}

void	input_redirect(t_command *root, t_redirection *root_redir, t_status *p)
{
	if (p->newfd_in < 0)
		dup_failed(root, p, 0);
	if (dup2(root_redir->fd, 0) == -1)
		dup_failed(root, p, 2);
	close(root_redir->fd);
}

int	out_redir(t_command *root, t_redirection *root_rdir, t_status *p, int cmd)
{
	root_rdir->fd = open(root_rdir->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (root_rdir->fd == -1)
	{
		write(2, "minishell : ", 12);
		perror(root_rdir->file);
		p->check_redir = 1;
		p->exit_status = 1;
		return (1);
	}
	else if (cmd == -1)
		return (0);
	else
		out_redirect(root, root_rdir, p);
	return (0);
}

int	in_redir(t_command *root, t_redirection *root_redir, t_status *p, int cmd)
{
	root_redir->fd = open(root_redir->file, O_RDONLY, 0644);
	if (root_redir->fd == -1)
	{
		write(2, "minishell : ", 12);
		perror(root_redir->file);
		p->check_redir = 1;
		p->exit_status = 1;
		return (1);
	}
	else if (cmd == -1)
		return (0);
	else
		input_redirect(root, root_redir, p);
	return (0);
}
