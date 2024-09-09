/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cahaik <cahaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 07:45:26 by cahaik            #+#    #+#             */
/*   Updated: 2024/08/28 19:12:47 by cahaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

typedef struct trees
{
	int data;
	struct trees *left;
	struct trees *right;
}	t_tree;

t_tree *create_node(int value)
{
	t_tree *node;
	node = malloc(sizeof(t_tree));
	if (!node)
		return (NULL);
	node->data = value;
	node->left = NULL;
	node->right = NULL;
	return (node);
}  
// void postOrderTraversal(t_tree *node)
// {
// 	if (!node)
// 		return ;
// 	postOrderTraversal(node->left);
// 	postOrderTraversal(node->right);
// 	printf("data = %d\n", node->data);
// }

// int countNodes(t_tree *node)
// {
// 	int count;

// 	count = 0;
// 	if (!node)
// 		return (count);
// 	else
// 		count++;
// 	count += countNodes(node->left);
// 	count += countNodes(node->right);
// 	return (count);
// }

// int maxValue(t_tree *node)
// {
// 	int max;
	
// 	if (!node)
// 		return (max);
// 	if (node->data >= max)
// 		max = node->data;
// 	max = maxValue(node->left);
// 	max = maxValue(node->right);
// 	return (max);
// }

// int maxDepth(t_tree *node)
// {
// 	int left;
// 	int right;
	
// 	if(!node)
// 		return(0);
	
// 	left =1 + maxDepth(node->left);
// 	right =1 + maxDepth(node->right);
// 	if (left >= right)
// 		return (left);
// 	return (right);
// }



int main()
{
	int i;
	t_tree *root;
	t_tree *node1;
	t_tree *node2;
	t_tree *node3;
	t_tree *node4;
	t_tree *node5;
	t_tree *node6;

	i = 0;
	root = create_node(10);
	node1 = create_node(5);
	node2 = create_node(20);
	node3 = create_node(0);
	node4 = create_node(3);
	node5 = create_node(4);
	node6 = create_node(7);
	
	root->left = node1;
	root->right = node2;
	node1->left = node3;
	node1->right = node4;
	node2->left = node5;
	node2->right = node6;
	//preOrderTraversal(root);
	//inOrderTraversal(root);
	//postOrderTraversal(root);
	// printf("there are %d nodes\n", countNodes(root));
	// printf("the max depth is %d\n", maxValue(root));
	// printf("the max depth is %d\n", maxDepth(root));
	return (0);
}


/* 
pipes are used to pass data between processes
pipe() to create pipe , pipe means two processes , 
pipe()----> creates unidirectioa; data channel (for communication) between 2 processes
 that has two
ends : write end (output : where data is wtitten) + read end (input : where data is read)

dup2() ----> to redirect the standard output and input
redirect 'stdout' to the write end of the pipe
stdin to the read end

pipefd[0] is for reading from the pipe
pipefd[1] is for writing to the pipe