/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykamboua <ykamboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 22:37:14 by ykamboua          #+#    #+#             */
/*   Updated: 2024/11/02 06:45:21 by ykamboua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// int is_token(char c) 
// {
//     return (c == '|' || c == '<' || c == '>');
// }
int is_token(char c, char c_1) 
{
	if((c == '<' && c_1 == '<') || (c == '>' && c == '>'))
		return (1);
	else if(c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

int define_type(char c, char c_1)
{
	int type;

	type = 0;

	if (c == '|')
		type = PIPE;
	else if (c == '<')
	{
		if(c_1 == '<')
			return(type = HERDOC);
		type = I_RED;
	}
	else if (c == '>')
	{
		if(c_1 == '>')
			return(type = APPEND);
		type = O_RED;
	}
	return (type);
}


int append_special_tokens(t_command *data, char c, char c_1)
{
	int			type;
	int			res;
	char		*token;
	t_tokens	*new_node;

	res = 1;
	type = define_type(c, c_1);
	if (type == PIPE)
	{
		// return (token = ft_strdup("|"), res= 1, res);
		token = ft_strdup("|");
		// res = 1;
	}
	else if (type == I_RED)
	{
		token = ft_strdup("<");
		// res = 1;
	}
	else if (type == O_RED)
	{
		token = ft_strdup(">");
		// res = 1;
	}
	else if (type == HERDOC)
	{
		token = ft_strdup("<<");
		res = 2;
	}
	else if (type == APPEND)
	{
		token = ft_strdup(">>");
		res = 2;
	}
	new_node = ft_lstneww(token, type);
	ft_lstadd_backk(&(data->tokens_list), new_node);
	return (res);
}


int is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

int quotes_handler(char *input, int start, char quote_char)
{
	int	i;

	i = start + 1;
	while (input[i])
	{
		if (input[i] == quote_char)
			return (i);
		i++;
	}
	// printf("&&&%d\n", i);
	printf("--00--(%c)\n", input[i]);
	return (-1);
}

int word_handler(char *input, int start, int *type)
{
	int i = start;

	*type = WORD;
	while (input[i] && !is_whitespace(input[i]) && !is_token(input[i], input[i + 1])) 
	{
		if (input[i] == '\'' || input[i] == '\"')
		{
			// *type = WORD;
			i = quotes_handler(input, i, input[i]);
			if (i == -1) 
			{
				printf("saad lquoootes !\n");
				exit(1);
				// return (-1);
			}
		}
		if(input[i] == ' ' || is_token(input[i], input[i + 1]))
			break;
		i++;
	}
	return (i);
}

void lexer(t_command	*data)
{
	int 		i;
	int			start;
	int 		type;
	char 		*token;
	t_tokens	*new_token;

	i = 0;
	while (data->cmnd[i])
	{
		while (is_whitespace(data->cmnd[i]))
			i++;
		if(!is_token(data->cmnd[i], data->cmnd[i + 1]))
		{
			start = i;
			i = word_handler(data->cmnd, i, &type);
			token = ft_substr(data->cmnd, start, i - start);
			if (token && ft_strlen(token))
			{
				new_token = ft_lstneww(token, type);
				ft_lstadd_backk(&(data->tokens_list), new_token);
			}
			free(token);
			// free(new_token);
		}
		if(is_token(data->cmnd[i], data->cmnd[i + 1]))
		{
			i+= append_special_tokens(data, data->cmnd[i], data->cmnd[i + 1]);
		}
	}
}

int main()
{
	t_command 	data;
	t_command	*tree;
	
	t_tokens *token_node;
	char *str;

	str = readline("minii>");
	while (str)
	{
		data.cmnd = str;
		data.tokens_list = NULL;
		lexer(&data);
		token_node = data.tokens_list;
		expand_env(data.tokens_list);
		remove_quotes((data.tokens_list));
		tree = build_ast(data.tokens_list);
		// printf("%s\n",tree->cmnd);
		int i = 0;
		while (tree->args[i])
		{
			printf("%s\n", tree->args[i]);
			i++;
		}
		
		// while (token_node) 
		// {
		// 	printf("Token : (%s)\n", token_node->value);
		// 	// printf("type : (%d)\n", token_node->type);
		// 	// printf("Token : (%d)\n", token_node->type);
		// 	token_node = token_node->next;
		// }
		free(str);  
		str = readline("minii>");
	}
	return 0;
}
