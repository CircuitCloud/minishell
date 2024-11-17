/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cahaik <cahaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 18:49:48 by cahaik            #+#    #+#             */
/*   Updated: 2024/11/17 07:05:13 by cahaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	left_child(t_command *root, int *fd, pid_t *left_pid, t_status **p)
{
	(*left_pid) = fork();
	if ((*left_pid) == -1)
	{
		perror("fork");
		(*p)->exit_status = 1;
		exit((*p)->exit_status);
	}
	else if ((*left_pid) == 0)
	{
		close(fd[0]);
		dup2(fd[1], 1);
		close(fd[1]);
		execute_program(root->left, p);
		exit((*p)->exit_status);
	}
}

void	right_child(t_command *root, int *fd, pid_t *right_pid, t_status **p)
{
	(*right_pid) = fork();
	if ((*right_pid) == -1)
	{
		write(2, "minishell : ", 12);
		perror("fork");
		(*p)->exit_status = 1;
		exit((*p)->exit_status);
	}
	else if ((*right_pid) == 0)
	{
		close(fd[1]);
		dup2(fd[0], 0);
		close(fd[0]);
		execute_program(root->right, p);
		exit((*p)->exit_status);
	}
}

void	execute_pipe(t_command *root, t_status **p)
{
	int		fd[2];
	pid_t	left_pid;
	pid_t	right_pid;
	int		status;
	
	left_pid = 0;
	right_pid = 0;
	if (pipe(fd) == -1)
	{
		write(2, "minishell : ", 12);
		perror("pipe");
		(*p)->exit_status = 1;
		exit((*p)->exit_status);
	}
	if (root && root->left)
		left_child(root, fd, &left_pid, p);
	if (root && root->right)
		right_child(root, fd, &right_pid, p);
	close(fd[0]);
	close(fd[1]);
	waitpid(left_pid, &status, 0);
	waitpid(right_pid, &status, 0);
	if (WIFSIGNALED(status))
		(*p)->exit_status = WTERMSIG(status) + 128;
	else
		(*p)->exit_status = WEXITSTATUS(status);
}
