/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cahaik <cahaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 05:42:44 by cahaik            #+#    #+#             */
/*   Updated: 2024/01/08 22:49:14 by cahaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	int				i;
	unsigned char	*to;
	unsigned char	*from;

	i = len - 1;
	to = (unsigned char *)dest;
	from = (unsigned char *)src;
	if (len == 0)
		return ((char *)dest);
	if (!src && !dest)
		return (NULL);
	if (to < from)
		ft_memcpy(dest, src, len);
	else
	{
		while (i >= 0)
		{
			to[i] = from[i];
			i--;
		}
	}
	return (dest);
}
