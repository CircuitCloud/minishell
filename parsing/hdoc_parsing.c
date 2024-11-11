/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdoc_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykamboua <ykamboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 01:15:37 by ykamboua          #+#    #+#             */
/*   Updated: 2024/11/10 06:07:28 by ykamboua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"
// char	*find_delimiter(char *cmnd)
// {
// 	int	
// }
#include "strings.h"

t_hdoc_inputs	*create_hdoc_inode(char *line)
{
	t_hdoc_inputs	*hdoc_inode;

	hdoc_inode = malloc(sizeof(t_hdoc_inputs));
	hdoc_inode->value = strdup(line);
	hdoc_inode->next = NULL;
	return (hdoc_inode);
}

int	hdoc_parser(t_tokens *tokens)
{
	t_tokens	*current;
	char	*delimiter = NULL;
	t_hdoc_inputs	*inputs = NULL;
	t_hdoc_inputs	*last;
	char	*line;
	int		fd;
	
	int	i;
	
	i = 0;
	current = tokens;

	while (current)
	{
		if(strncmp(current->value, "<<", 2) == 0 && current->next)
		{
			delimiter = current->next->value;
			break;
		}
		current = current->next;
	}
	if(delimiter)
	{
		fd = open("inputs.txt", O_CREAT | O_WRONLY | O_TRUNC, 0600);
		if(fd < 0)
		{
			printf("error fd < 0\n");
		}
		while (1)
		{
			line = readline(">");
			if(!line)
				break;			
			if(strncmp(line, delimiter, strlen(delimiter) + 1) == 0)
			{
				free(line);
				break;
			}
			write(fd, line, strlen(line));
			write(fd, "\n", 1);
			free(line);
		}
		close(fd);
		return (fd);
	}
	return (-1);
}


t_tokens	*ft_lstnewww(char *cmnd, int type)
{
	t_tokens	*command;

	command = (t_tokens *)malloc(sizeof(t_tokens));
	if (!command)
		return (NULL);
	command -> value = cmnd;;
	command -> type = type;
	command -> next = NULL;
	return (command);
}