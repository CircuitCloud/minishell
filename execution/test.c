/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cahaik <cahaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 18:49:48 by cahaik            #+#    #+#             */
/*   Updated: 2024/09/14 17:28:20 by cahaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command *create_tree(char **env)
{
	t_command *node;
	
	node = malloc(sizeof(t_command));
	if (!node)
		return (NULL);
	node->args = malloc(sizeof(char *) * 2);
	node->args[0] = "|";
	node->args[1] = NULL;
	node->ev = env;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

t_command *create_left(char **env)
{
	t_command *node;
	
	node = malloc(sizeof(t_command));
	if (!node)
		return (NULL);
	node->args = malloc(sizeof(char *) * 3);
	node->args[0] = "ls";
	node->args[1] = "-la";
	node->args[2] = NULL;
	node->ev = env;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

t_command *create_right(char **env)
{
	t_command *node;
	
	node = malloc(sizeof(t_command));
	if (!node)
		return (NULL);
	node->args = malloc(sizeof(char *) * 3);
	node->redir = malloc(sizeof(t_redirection));
	node->args[0] = "cat";
	node->args[1] = "pipes.c";
	node->redir->file = "test.c";
	node->redir->type = APPEND_RED;
	node->args[2] = NULL;
	node->ev = env;
	node->left = NULL;
	node->right = NULL;
	return (node);
}
t_command *create_right_child(char **env)
{
	t_command *node;
	
	node = malloc(sizeof(t_command));
	if (!node)
		return (NULL);
	node->args = malloc(sizeof(char *) * 3);
	node->args[0] = "grep";
	node->args[1] = "root";
	node->args[2] = NULL;
	node->ev = env;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

int execute_pipe(t_command *root)
{
	int fd[2];
	pid_t left_pid;
	pid_t right_pid;

	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit(1);
	}
	if (root && root->left)
	{
		left_pid = fork();
		if (left_pid == -1)
		{
			perror("fork");
			exit(1);		
		}
		else if (left_pid == 0)
		{
			close(fd[0]);
			dup2(fd[1], 1);
			close(fd[1]);
			execute_program(root->left);
			exit (0);
		}
	}
	if (root && root->right)
	{
		right_pid = fork();
		if (right_pid == -1)
		{
			perror("fork");
			exit(1);		
		}
		else if (right_pid == 0)
		{
			close(fd[1]);
			dup2(fd[0], 0);
			close(fd[0]);
			execute_program(root->right);
			exit(0);
		}
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(left_pid, NULL, 0);
	waitpid(right_pid, NULL, 0);
	return (1);
}
