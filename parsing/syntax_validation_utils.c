/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_validation_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykamboua <ykamboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 17:19:33 by ykamboua          #+#    #+#             */
/*   Updated: 2024/11/26 12:03:53 by ykamboua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_valid_start(t_tokens *tokens, int d)
{
	int	i;

	i = 0;
	if (tokens && tokens->type == d)
		return (1);
	return (0);
}

int	is_valid_end(t_tokens *tokens)
{
	t_tokens	*last;

	if (!tokens)
		return (1);
	last = ft_lstlastt(tokens);
	if (last->type != WORD)
	{
		return (1);
	}
	return (0);
}

int	duplicate_operator(t_tokens *tokens, int type)
{
	while (tokens)
	{
		if (tokens->type == type)
		{
			if (tokens->type == tokens->next->type)
				return (1);
		}
		tokens = tokens->next;
	}
	return (0);
}

int	valid_next(t_tokens *tokens, char *c)
{
	while (tokens)
	{
		if (tokens->type == I_RED || tokens->type == O_RED 
			|| tokens->type == HERDOC || tokens->type == APPEND)
		{
			if (tokens->next->type != WORD)
			{
				(*c) = tokens->next->value[0];
				return (1);
			}
		}
		tokens = tokens->next;
	}
	return (0);
}
