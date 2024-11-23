/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykamboua <ykamboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 22:35:08 by cahaik            #+#    #+#             */
/*   Updated: 2024/11/23 04:13:39 by ykamboua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_f(char c, const char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	lens;

	i = 0;
	if (!s1 || !set)
		return (NULL);
	lens = ft_strlen(s1);
	if (lens == 0 || (lens == 0 && ft_strlen(set) == 0))
		return (ft_strdup(""));
	while (s1[i] && is_f(s1[i], set))
		i++;
	while (lens > 0 && s1[lens - 1] && is_f(s1[lens - 1], set))
		lens--;
	return (ft_substr(s1, i, lens - i));
}

char	*ft_strtrim_execution(char const *s1, char const *set)
{
	size_t	i;
	size_t	lens;

	i = 0;
	if (!s1 || !set)
		return (NULL);
	lens = ft_strlen(s1);
	if (lens == 0 || (lens == 0 && ft_strlen(set) == 0))
		return (ft_strdup(""));
	while (is_f(s1[lens - 1], set) && s1[lens - 1])
		lens--;
	return (ft_substr(s1, 0, lens));
}
