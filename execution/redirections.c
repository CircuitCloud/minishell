/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cahaik <cahaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 09:43:40 by cahaik            #+#    #+#             */
/*   Updated: 2024/09/14 17:33:54 by cahaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void out_redirect(t_command *root)
{
	if (dup2(root->redir->fd, 1) == -1) {
        perror("dup2 failed");
        close(root->redir->fd);
        return;
    }
    close(root->redir->fd);
	// execute_program(root);
}

void input_redirect(t_command *root)
{
	if (dup2(root->redir->fd, 0) == -1) {
        perror("dup2 failed");
        close(root->redir->fd);
        return;
    }
    close(root->redir->fd);
	// execute_program(root);
}

void redirection(t_command *root)
{	
	if (root->redir->type == OUTPUT_RED)
	{
		root->redir->fd = open(root->redir->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (root->redir->fd == -1)
		{
			write(2, "failed to open file\n", 20);
			return ;
		}
		else
			out_redirect(root);
	}
	else if (root->redir->type == INPUT_RED || root->redir->type == HERE_DOC)
	{
		root->redir->fd = open(root->redir->file, O_RDONLY, 0644);
		if (root->redir->fd == -1)
		{
			write(2, "failed to open file\n", 20);
			return ;
		}
		else
			input_redirect(root);
	}
	else if (root->redir->type == APPEND_RED)
	{
		root->redir->fd = open(root->redir->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (root->redir->fd == -1)
		{
			write(2, "failed to open file\n", 20);
			return ;
		}
		else
			out_redirect(root);
	}
}

// unlink heredoc's file when i finish working 