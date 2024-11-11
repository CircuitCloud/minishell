/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_validation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykamboua <ykamboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 17:05:39 by ykamboua          #+#    #+#             */
/*   Updated: 2024/09/29 05:25:39 by ykamboua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	syntaxe_validation(char *token)
{
	if(is_valid_start(token, '|') || is_valid_start(token, '<') || is_valid_start(token, '>'))
		return (1);
	if(is_valid_end(token, '|') || is_valid_end(token, '<') || is_valid_end(token, '>'))
		return(1);
	if(duplicate_operator(token, '|'))
		return (1);
	if(open_quotes_check(token))
		return (1);
	if(consecutive_operators_check(token, '|'))
		return (1);
	return (0);
}