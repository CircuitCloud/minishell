/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykamboua <ykamboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 03:49:10 by ykamboua          #+#    #+#             */
/*   Updated: 2024/11/26 11:55:22 by ykamboua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_token(char c, char c_1)
{
	if (c && c_1 && ((c == '<' && c_1 == '<') || (c == '>' && c == '>')))
		return (1);
	else if (c && (c == '|' || c == '<' || c == '>'))
		return (1);
	return (0);
}

int	define_type(char c, char c_1)
{
	if (c == '|')
		return (PIPE);
	else if (c == '<')
	{
		if (c_1 && c_1 == '<')
			return (HERDOC);
		return (I_RED);
	}
	else if (c == '>')
	{
		if (c_1 && c_1 == '>')
			return (APPEND);
		return (O_RED);
	}
	return (0);
}

int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

int	quotes_handler(char *input, int start, char quote_char)
{
	int	i;

	i = start + 1;
	if (!input || start >= ft_strlen(input) || start < 0)
		return (-1);
	while (input[i])
	{
		if (input[i] == quote_char)
			return (i);
		i++;
	}
	return (-1);
}

int	word_handler(char *input, int start)
{
	int	i;

	i = start;
	if (!input || start < 0 || start >= ft_strlen(input))
		return (-1);
	while (input[i] && !is_whitespace(input[i]) 
		&& !is_token(input[i], input[i + 1])) 
	{
		if (input[i] == '\'' || input[i] == '\"')
		{
			i = quotes_handler(input, i, input[i]);
			if (i == -1) 
			{
				printf("minishell : no closing quote found\n");
				return (-1);
			}
		}
		if (input[i] == ' ' || is_token(input[i], input[i + 1]))
			break ;
		i++;
	}
	return (i);
}
