/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykamboua <ykamboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 04:15:12 by ykamboua          #+#    #+#             */
/*   Updated: 2024/11/26 11:53:33 by ykamboua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*dup_special_token(int type, int *res)
{
	char		*token;

	if (type == PIPE)
		token = ft_strdup("|");
	else if (type == I_RED)
		token = ft_strdup("<");
	else if (type == O_RED)
		token = ft_strdup(">");
	else if (type == HERDOC)
	{
		token = ft_strdup("<<");
		*res = 2;
	}
	else if (type == APPEND)
	{
		token = ft_strdup(">>");
		*res = 2;
	}
	return (token);
}

int	append_special_tokens_2(t_command *data, char *token, int type)
{
	t_tokens	*new_node;

	new_node = ft_lstneww(token, type);
	if (!new_node)
	{
		free(token);
		return (1);
	}
	ft_lstadd_backk(&(data->tokens_list), new_node);
	return (0);
}

int	append_special_tokens(t_command *data, char c, char c_1)
{
	int			type;
	int			res;
	char		*token;

	res = 1;
	token = NULL;
	type = define_type(c, c_1);
	if (!data)
		return (-1);
	token = dup_special_token(type, &res);
	if (!token)
		return (-1);
	if (append_special_tokens_2(data, token, type) == 1)
		return (-1);
	free(token);
	return (res);
}

int	append_word(t_command *data, int *i)
{
	t_tokens	*new_token;
	char		*token;
	int			start;

	if (!is_token(data->cmnd[*i], data->cmnd[*i + 1]))
	{
		start = *i;
		*i = word_handler(data->cmnd, *i);
		if (*i == -1)
			return (1);
		token = ft_substr(data->cmnd, start, *i - start);
		if (!token)
			return (1);
		if (token && ft_strlen(token))
		{
			new_token = ft_lstneww(token, WORD);
			if (!new_token)
				return (free(token), 1);
			ft_lstadd_backk(&(data->tokens_list), new_token);
		}
		free(token);
	}
	return (0);
}

int	lexer(t_command	*data)
{
	int			i;
	int			start;
	t_tokens	*new_token;
	int			append_result;

	i = 0;
	if (!data || !data->cmnd)
		return (1);
	while (data->cmnd[i])
	{
		while (is_whitespace(data->cmnd[i]))
			i++;
		if (append_word(data, &i))
			return (free_tokens_list(data->tokens_list), 1);
		if (data->cmnd && data->cmnd[i] 
			&& is_token(data->cmnd[i], data->cmnd[i + 1]))
		{
			append_result = 
				append_special_tokens(data, data->cmnd[i], data->cmnd[i + 1]);
			if (append_result < 0)
				return (free_tokens_list(data->tokens_list), 1);
			i += append_result;
		}
	}
	return (0);
}
