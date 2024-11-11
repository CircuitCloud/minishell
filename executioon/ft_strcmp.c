/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cahaik <cahaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 09:19:40 by cahaik            #+#    #+#             */
/*   Updated: 2024/11/07 04:02:59 by cahaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strcmp(char *dest, char *src)
{
	size_t	i;

	i = 0;
	while (dest[i] || src[i])
	{
		if (!((unsigned char)dest[i] == (unsigned char)src[i]))
			return ((unsigned char)dest[i] - (unsigned char)src[i]);
		i++;
	}
	return (0);
}
