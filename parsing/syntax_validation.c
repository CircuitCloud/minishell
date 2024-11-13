/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_validation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cahaik <cahaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 17:05:39 by ykamboua          #+#    #+#             */
/*   Updated: 2024/11/12 23:47:51 by cahaik           ###   ########.fr       */
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
		printf("vaaliiid start asiii\n");
		return (1);
	}
	if(is_valid_end(token, PIPE) || is_valid_end(token, I_RED) || is_valid_end(token, O_RED) || is_valid_end(token, HERDOC) || is_valid_end(token, APPEND))
	{
		printf("vaalid end assiii\n");
		return(1);
	}
	if(duplicate_operator(token, PIPE) || duplicate_operator(token, I_RED) || duplicate_operator(token, O_RED) || duplicate_operator(token, APPEND) || duplicate_operator(token, HERDOC))
	{
		printf("duup opppe\n");
		return (1);
	}
	return (0);
}
