/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdoc_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykamboua <ykamboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 01:15:37 by ykamboua          #+#    #+#             */
/*   Updated: 2024/11/22 00:49:45 by ykamboua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

#include "strings.h"

char	*hdoc_expand_handler(char *token, t_ev *ev, t_status **p)
{
	char	*str;
	char	*var_name;
	int		i, start;
	int		single_quoted = 0;
	int		double_quoted = 0;
	char	*env_value;

	str = ft_strdup("");
	i = 0;

	while (token[i])
	{
		if (token[i] == '$')
		{
			i++;
			if(!token[i])
			{
				str = ft_strjoin(str, "$");
			}
			if (ft_isdigit(token[i]))
				i++;
			else if (ft_isalpha(token[i]) || token[i] == '_')
			{
				var_name = extract_var(token, &i);
				env_value = search_ev_value(var_name, ev);
				if (!env_value)
					env_value = "";
				str = ft_strjoin(str, env_value);
				free(var_name);
			}
			else if (token[i] == '?')
			{
				str = ft_strjoin(str, ft_itoa((*p)->exit_status));
				i++;
			}
		}
		start = i;
		while (token[i] && token[i] != '$' && token[i] != '\'' && token[i] != '"')
			i++;
		if (i > start)
			str = ft_strjoin(str, ft_substr(token, start, i - start));
	}
	return (str);
}


// int	hdoc_parser(t_tokens *tokens)
// {
// 	t_tokens	*current;
// 	char	*delimiter = NULL;
// 	t_hdoc_inputs	*inputs = NULL;
// 	t_hdoc_inputs	*last;
// 	char	*line;
// 	int		fd;
	
// 	int	i;
	
// 	i = 0;
// 	current = tokens;

// 	while (current)
// 	{
// 		if(strncmp(current->value, "<<", 2) == 0 && current->next)
// 		{
// 			delimiter = current->next->value;
// 			break;
// 		}
// 		current = current->next;
// 	}
// 	if(delimiter)
// 	{
// 		fd = open("inputs.txt", O_CREAT | O_WRONLY | O_TRUNC, 0600);
// 		if(fd < 0)
// 		{
// 			printf("error fd < 0\n");
// 		}
// 		while (1)
// 		{
// 			line = readline(">");
// 			if(!line)
// 				break;			
// 			if(strncmp(line, delimiter, strlen(delimiter) + 1) == 0)
// 			{
// 				free(line);
// 				break;
// 			}
// 			write(fd, line, strlen(line));
// 			write(fd, "\n", 1);
// 			free(line);
// 		}
// 		close(fd);
// 		return (fd);
// 	}
// 	return (-1);
// }


// t_tokens	*ft_lstnewww(char *cmnd, int type)
// {
// 	t_tokens	*command;

// 	command = (t_tokens *)malloc(sizeof(t_tokens));
// 	if (!command)
// 		return (NULL);
// 	command -> value = cmnd;;
// 	command -> type = type;
// 	command -> next = NULL;
// 	return (command);
// }
