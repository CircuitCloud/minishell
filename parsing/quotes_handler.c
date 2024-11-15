/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykamboua <ykamboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 20:27:54 by ykamboua          #+#    #+#             */
/*   Updated: 2024/11/16 00:13:36 by ykamboua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


char	*quotes_eliminator(char *token)
{
	int		i;
	char	*str;
	char	*tmp;
	int		single_quoted;
	int		double_quoted;

	single_quoted = 0;
	double_quoted = 0;
	str = ft_strdup("");
	i = 0;

	while (token[i])
	{
		if ((token[i] == '"' && !single_quoted) || (token[i] == '\'' && !double_quoted))
		{
			if(token[i] == '\'')
				single_quoted = !single_quoted;
			else if (token[i] == '"')
				double_quoted = !double_quoted;
			i++;
		}
		// if(token[i])
		else
		{
			tmp = str;
			str = ft_strjoin(str, ft_substr(token, i, 1));
			free(tmp);
			i++;
		}
	}
	return (str);
}


void	remove_quotes(t_tokens *tokens)
{
	while (tokens)
	{
		if(tokens->type == WORD)
		{
			tokens->value = quotes_eliminator(tokens->value);
		}
		tokens = tokens->next;
	}
}
