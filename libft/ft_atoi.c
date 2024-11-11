/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cahaik <cahaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 09:32:47 by cahaik            #+#    #+#             */
/*   Updated: 2024/01/09 15:55:13 by cahaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	size_t	i;
	t_help	n;

	i = 0;
	n.sign = 1;
	n.number = 0;
	while ((str[i] == ' ') || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			n.sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		n.cpy = n.number;
		n.number = (n.number * 10) + (str[i] - '0');
		if (n.cpy > n.number && n.sign == 1)
			return (-1);
		if (n.cpy > n.number && n. sign == -1)
			return (0);
		i++;
	}
	return ((int)(n.sign * n.number));
}
