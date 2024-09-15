/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cahaik <cahaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 08:49:07 by cahaik            #+#    #+#             */
/*   Updated: 2024/01/08 22:49:07 by cahaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		i;
	char		*to;
	const char	*from = src;

	i = 0;
	to = dest;
	if (src == dest)
		return (dest);
	if (!src && !dest)
		return (NULL);
	while (i < n)
	{
		to[i] = from[i];
		i++;
	}
	return (dest);
}
