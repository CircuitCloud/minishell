/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_util2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cahaik <cahaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 07:54:31 by cahaik            #+#    #+#             */
/*   Updated: 2024/11/29 00:19:44 by cahaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	status_exec_program(int status, int c)
{
	if (WIFSIGNALED(status))
	{
		if (c == 0)
			return (WTERMSIG(status) + 128);
		else
			return (WTERMSIG(status)); 
	}
	else
		return (WEXITSTATUS(status));
}

void	fork_failed(t_status *p)
{
	write(2, "minishell : ", 12);
	perror("fork");
	p->exit_status = 1;
	free_splited(p->env);
	exit(p->exit_status);
}

void	unlink_(t_command root)
{
	while (root.redir)
	{
		if (root.redir->file && root.redir->type == HERDOC)
		{
			unlink(root.redir->file);
		}
		root.redir = root.redir->next_redir;
	}
}

void	original_fd(t_command *root, t_status *p)
{
	if (p->last_herdoc != 0)
		unlink_(*root);
	if (p->for_redir_check == 2)
	{
		if (dup2(p->newfd_out, 1) == -1 || dup2(p->newfd_in, 0) == -1)
			dup_failed(root, p, 2);
		close(p->newfd_out);
		close(p->newfd_in);
	}
	p->for_redir_check = 0;
}
