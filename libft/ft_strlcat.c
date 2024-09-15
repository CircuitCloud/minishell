/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cahaik <cahaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 11:40:19 by cahaik            #+#    #+#             */
/*   Updated: 2024/01/08 22:50:05 by cahaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	n;
	size_t	j;

	i = ft_strlen(dest);
	n = i;
	j = 0;
	if (size <= ft_strlen(dest))
		return (size + ft_strlen(src));
	while (src[j] && i < (size - 1))
	{
		dest[i++] = src[j++];
	}
	dest[i] = '\0';
	size = n + ft_strlen(src);
	return (size);
}
