/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cahaik <cahaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 23:29:35 by cahaik            #+#    #+#             */
/*   Updated: 2024/09/12 23:33:33 by cahaik           ###   ########.fr       */
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
	node->args[0] = "cat";
	node->args[1] = "pipes.c";
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
			
			execute_program(root->left->args, root->ev);
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
			
			execute_program(root->right->args, root->ev);
		}
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(left_pid, NULL, 0);
	waitpid(right_pid, NULL, 0);
	return (1);
}

// creating one pipe
int main(int ac, char **av, char **ev)
{
	t_command *root;
	t_command *left;
	t_command *right;

	(void)ac;
	(void)av;
	root = create_tree(ev);
	left = create_left(ev);
	right = create_right(ev);

	root->left = left;
	root->right = right;

	if (ft_strcmp(root->args[0], "|") == 0)
		execute_pipe(root);
	return (0);
}