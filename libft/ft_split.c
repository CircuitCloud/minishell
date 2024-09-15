/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cahaik <cahaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 18:00:55 by cahaik            #+#    #+#             */
/*   Updated: 2024/01/08 22:49:52 by cahaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count(const char *str, char c)
{
	size_t	counter;
	size_t	i;
	size_t	substring;

	i = 0;
	counter = 0;
	while (str[i])
	{
		substring = 0;
		while (str[i] == c && str[i])
			i++;
		while (str[i] != c && str[i])
		{
			if (substring == 0)
			{
				counter++;
				substring++;
			}
			i++;
		}
	}
	return (counter);
}

static int	ft_fill_free(char **t, size_t index)
{
	size_t	j;

	j = 0;
	if (!t[index])
	{
		while (j < index)
		{
			free(t[j]);
			j++;
		}
		free(t);
		return (1);
	}
	return (0);
}

char	**ft_split(const char *s, char c)
{
	char	**t;
	t_help	nb;

	nb.i = 0;
	nb.index = 0;
	if (!s)
		return (NULL);
	t = (char **)malloc((ft_count(s, c) + 1) * sizeof(char *));
	if (!t)
		return (NULL);
	t[ft_count(s, c)] = NULL;
	while (s[nb.i] && nb.i < ft_strlen(s) && nb.index < ft_count(s, c))
	{
		while (s[nb.i] == c && s[nb.i])
			nb.i++;
		nb.start = nb.i;
		while (s[nb.i] != c && s[nb.i])
			nb.i++;
		t[nb.index] = ft_substr(s, nb.start, nb.i - nb.start);
		if (ft_fill_free(t, nb.index) == 1)
			return (NULL);
		nb.index++;
	}
	return (t);
}
