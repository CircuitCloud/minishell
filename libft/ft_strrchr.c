/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cahaik <cahaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 10:10:03 by cahaik            #+#    #+#             */
/*   Updated: 2024/09/09 12:02:15 by cahaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*end;

	if (!s)
		return (NULL);
	end = (char *)s + ft_strlen(s);
	if ((char)c == '\0')
		return ((char *)(s + ft_strlen(s)));
	while (end >= s)
	{
		if ((unsigned char)*end == (unsigned char)c)
			return ((char *)end);
		end--;
	}
	return (NULL);
}
