/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cahaik <cahaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 01:58:14 by cahaik            #+#    #+#             */
/*   Updated: 2024/01/04 18:04:05 by cahaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*p;
	t_list	*mynode;

	if (!lst || !del)
		return ;
	p = *lst;
	while (p != NULL)
	{
		mynode = p;
		p = p->next;
		ft_lstdelone(mynode, del);
	}
	*lst = NULL;
}
