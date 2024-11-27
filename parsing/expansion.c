/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cahaik <cahaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 00:15:56 by ykamboua          #+#    #+#             */
/*   Updated: 2024/11/27 04:31:55 by cahaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env_token(char *token, t_ev *ev, t_status *p)
{
	t_expand_data	data;

	data.token = token;
	data.double_quoted = 0;
	data.single_quoted = 0;
	data.i = 0;
	data.str = ft_strdup("");
	while (token[data.i])
	{
		if (token[data.i] == '\'' && !data.double_quoted)
			expand_single_quotes(&data);
		if (token[data.i] == '"' && !data.single_quoted)
			expand_double_quotes(&data, ev, p);
		if (token[data.i] == '$' && !data.single_quoted)
			expd_no_quoted_word(&data, ev, p);
		data.start = data.i;
		while (token[data.i] && token[data.i] != '$' 
			&& token[data.i] != '\'' && token[data.i] != '"')
			data.i++;
		if (data.i > data.start)
			data.str = safe_ft_strjoin(data.str, 
					ft_substr(token, data.start, data.i - data.start), 1);
	}
	return (free_token(&token), data.str);
}

void	expand_env(t_tokens *tokens, t_ev *ev, t_status *p)
{
	while (tokens)
	{
		if (tokens->type == HERDOC)
		{
			if (tokens->next && (tokens->next->value[0] == '\'' 
					|| tokens->next->value[0] == '"'))
				tokens->hdoc_expand = 0;
			else
			{
				tokens->hdoc_expand = 1;
				if (tokens->next && tokens->next->type == WORD)
					tokens->raw_delimiter = ft_strdup(tokens->next->value);
			}
		}
		if (tokens->type == WORD)
		{
			tokens->value = get_env_token(tokens->value, ev, p);
			if (tokens && ft_strcmp(tokens->value, "") == 0)
				tokens->empty_expand = 1;
			else
				tokens->empty_expand = 0;
		}
		tokens = tokens->next;
	}
}
