/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cahaik <cahaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 18:49:48 by cahaik            #+#    #+#             */
/*   Updated: 2024/09/11 00:52:41 by cahaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command *create_tree(char **env)
{
	t_command *node;
	
	node = malloc(sizeof(t_command));
	if (!node)
		return (NULL);
	node->args = malloc(sizeof(char *) * 1);
	node->args[0] = "|";
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
	node->args[1] = "-l";
	node->args[2] = "-a";
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
	node->args = malloc(sizeof(char *) * 2);
	node->args[0] = "grep";
	node->args[1] = "hi";
	node->ev = env;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

int execute_pipe(t_command *root)
{
	int fd[2];
	pid_t pid;

	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit(1);
	}
	if (root->left)
	{
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(1);		
		}
		else if (pid == 0)
		{
			close(fd[0]);
			dup2(fd[1], 0);
			close(fd[1]);
			
			execve(root->left->args[0], root->left->args, root->left->ev);
			perror("execve");
		}
	}
	if (root->right)
	{
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(1);		
		}
		else if (pid == 0)
		{
			close(fd[1]);
			dup2(fd[0], 1);
			close(fd[0]);
			
			execve(root->right->args[0], root->right->args, root->right->ev);
			perror("execve");
		}
	}
	close(fd[0]);
	close(fd[1]);
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