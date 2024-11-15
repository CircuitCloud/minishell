/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_validation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykamboua <ykamboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 17:05:39 by ykamboua          #+#    #+#             */
/*   Updated: 2024/11/16 00:13:06 by ykamboua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	syntaxe_validation(t_tokens *token)
{
	char	c;

	if(!token)
		return (1);
	if(is_valid_start(token, PIPE))
	{
		printf("syntax error near unexpected token | \n");
		return (1);
	}
	if(is_valid_end(token))
	{
		printf("syntax error near unexpected token `newline' \n");
		return(1);
	}
	if(duplicate_operator(token, PIPE))
	{
		printf("syntax error near unexpected token `|' \n");
		return (1);
	}
	if(valid_next(token, &c))
	{
		printf("syntax error near unexpected token %c\n", c);
		return (1);
	}	
	return (0);
}
