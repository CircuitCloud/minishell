/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_validation_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykamboua <ykamboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 17:19:33 by ykamboua          #+#    #+#             */
/*   Updated: 2024/11/12 12:55:45 by ykamboua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_valid_start(t_tokens *tokens, int d)
{
	int	i;
	i = 0;
	// printf("ikhan\n");
	if(tokens && tokens->type == d)
		return(1);
	return(0);
}

int	is_valid_end(t_tokens *tokens, int d)
{
	t_tokens	*last;
	
	if(!tokens)
		return (1);
	last = ft_lstlastt(tokens);
	if(last->type == d)
		return(1);
	return (0);
}

int	duplicate_operator(t_tokens *tokens, int type)
{
	while (tokens)
	{
		if(tokens->type == type)
		{
			if(tokens->type == tokens->next->type)
				return(1);
		}
		tokens = tokens->next;
	}
	return (0);
}
