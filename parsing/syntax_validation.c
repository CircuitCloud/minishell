/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_validation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykamboua <ykamboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 17:05:39 by ykamboua          #+#    #+#             */
/*   Updated: 2024/11/14 22:40:52 by ykamboua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	syntaxe_validation(t_tokens *token)
{
	// printf("tffoooo\n");
	if(!token)
		return (1);
	if(is_valid_start(token, PIPE))
	{
		printf("1vaaliiid start asiii\n");
		return (1);
	}
	if(is_valid_end(token))
	{
		printf("1vaalid end \n");
		return(1);
	}
	if(duplicate_operator(token, PIPE))
	{
		printf("duup pipe\n");
		return (1);
	}
	if(valid_next(token))
	{
		printf("1val next\n");
		return (1);
	}	
	return (0);
}
