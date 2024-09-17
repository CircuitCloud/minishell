/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykamboua <ykamboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 19:39:34 by ykamboua          #+#    #+#             */
/*   Updated: 2024/09/16 23:15:08 by ykamboua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_token(char c)
{
	int	i;

	i = 0;
	// while (c)
	// {
		if(c == '|' || c == '\'' || c == '\"' || c == '>' || c == '<')
			return (1);
	// }
	return (0);
}

char	*extarct_from_quotes(char *input, int index)
{
	int		i;
	int		start;
	int		end;
	char	*str;

	i = 0;
	start = -1;
	end = -1;
	while (input[i])
	{
		if(i == index)
		{
			start = i;
			break;
		}
		i++;
	}
	if(start == -1)
		return(NULL);
	i++;
	while (input[i])
	{
		if(input[i] == input[start])
		{
			end = i + 1;
			break;
		}
		i++;
	}
	if(end == -1)
		return(NULL);
	return (str = ft_substr(input, start, end - start), str);
}

// int	*extarct_from_quotes(char *input, int index)
// {
// 	int		i;
// 	int		start;
// 	int		end;
// 	char	*str;

// 	i = 0;
// 	start = -1;
// 	end = -1;
// 	while (input[i])
// 	{
// 		if(i == index)
// 		{
// 			start = i;
// 			break;
// 		}
// 		i++;
// 	}
// 	if(start == -1)
// 		return(-1);
// 	i++;
// 	while (input[i])
// 	{
// 		if(input[i] == input[start])
// 		{
// 			end = i + 1;
// 			break;
// 		}
// 		i++;
// 	}
// 	return (end);
// }

// int	token_position_finder(char *input)
// {
// 	int	i;
// 	int	pos;

// 	i = 0;
// 	while (input[i])
// 	{
// 		if(is_token(input[i]))
// 			pos = i;
// 		i++;
// 	}
// }

char	*ft_not_token(char *sub_input)
{
	int	i;
	i = 0;

	while (sub_input[i] && !is_token(sub_input[i]))
	{
		// printf("%c", input[i]);
		i++;
	}
	return (ft_substr(sub_input, 0, i));
}
// void	lexer(t_command *input)
// {
// 	int		i;
// 	char	*command;
// 	int		index;
// 	int		start;

// 	index = 0;
// 	input -> args = malloc(sizeof(char *));
// 	command = ft_strtrim(input->cmnd, " ");
// 	i = 0;

// 	while (command[i])
// 	{
// 		if(command[i] == '"' || command[i] == '\'')
// 		{
// 			input->args[index] = extarct_from_quotes(command, i);
// 			i+= ft_strlen(input->args[index]);
// 			index++;
// 		}
// 		if(is_token(command[i]))
// 		{
// 			input->args[index] = command[i];
// 			index++;
// 			i++;
// 		}
// 		start = i;
// 		while (command[i] && !is_token(command[i]) && command[i] != ' ')
// 		{
// 			i++;
// 		}
// 		input->args[index] = ft_substr(command, start, i - start);
// 		index++;		
// 	}
// 	input->args[index] = NULL;
	
// }
char **lexer(t_command *input)
{
    int i = 0;
    int index = 0;
    char *command;
	int start;
	 	
    input->args = malloc(sizeof(char *)); 
    command = ft_strtrim(input->cmnd, " "); 
    
    while (command[i])
    {
		// printf("Processing command[%d]: %c\n", i, command[i]);
        if (command[i] == ' ')
        {
            i++;
        }
        if (command[i] == '"' || command[i] == '\'')
        {
			// printf("----%s---\n", extarct_from_quotes(command, i));
			printf("555\n");
            input->args[index] = extarct_from_quotes(command, i); 
            i += ft_strlen(input->args[index]); 
            index++;
        }
        if (is_token(command[i]))
        {
            input->args[index] = ft_substr(command, i, 1); 
            index++;
            i++;
        }
        start = i;
        while (command[i] && !is_token(command[i]) && command[i] != ' ')
            i++;
		if (start != i) 
		{
            input->args[index] = ft_substr(command, start, i - start);
            index++;
        }
		i++;
    }
    input->args[index] = NULL;
	return (input->args);
}


int main()
{
	t_command *str;
	int i = 0;
	char **res;
	
	str->cmnd = "ech\"o\" st'u'ffab|cdef $SHLV|Lpizza";
	// res = ft_not_token(str);
	res = lexer(str);
	// printf("%s\n", res);
	while (res[i])
	{
		printf("%s\n", res[i]);
		i++;
	}
	// printf("---%s\n", extarct_from_quotes(str->cmnd, 14));
}