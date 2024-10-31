/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdoc_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykamboua <ykamboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 01:15:37 by ykamboua          #+#    #+#             */
/*   Updated: 2024/10/31 05:38:30 by ykamboua         ###   ########.fr       */
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
t_hdoc_inputs	*hdoc_parser(t_tokens *tokens)
{
	t_tokens	*current;
	char	*delimiter = NULL;
	t_hdoc_inputs	*inputs = NULL;
	t_hdoc_inputs	*last;
	char	*line;
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
	// current = current->next;
	// while (current && (strncmp(current->value, delimiter, strlen(delimiter)) == 0))
	// {
	// 	inputs[i] = current->value;
	// 	i++;
	// 	current = current->next;
	// }
	// line = readline(">");
	while (1)
	{
		line = readline(">");
		if(!line)
			break;
		
		if(strncmp(line, delimiter, strlen(delimiter)) == 0)
		{
			free(line);
			break;
		}

		t_hdoc_inputs *new_node = create_hdoc_inode(line);
		free(line);
		if(!inputs)
			inputs = new_node;
		else
			last->next = new_node;
		last = new_node;
		// inputs->next = create_hdoc_inode(line);
	}
	return (inputs);
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

int main()
{
	t_tokens	*str;
	str = ft_lstnewww("hello", 0);

	t_tokens	*str1;
	str1 = ft_lstnewww("<<",0);

	t_tokens	*str2;
	str2 = ft_lstnewww("dddd",0);
	t_tokens	*str3;
	str3 = ft_lstnewww("stop",0);
	
	t_tokens	*str4;
	str4 = ft_lstnewww("789",0);
	
	str->next= str1;
	str1->next= str2;
	str2->next= str3;
	str3->next= str4;
	
	int i ;
	i = 0;

	t_hdoc_inputs *inputs;
	inputs = hdoc_parser(str);

	while (inputs)
	{
		printf("%s\n", inputs->value);
		inputs= inputs->next;
	}
	
	// printf("%s", hdoc_parser(str));
}