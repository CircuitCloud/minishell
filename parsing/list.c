/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykamboua <ykamboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 21:46:23 by ykamboua          #+#    #+#             */
/*   Updated: 2024/11/08 05:28:19 by ykamboua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_tokens	*ft_lstneww(char *cmnd, int type)
{
	t_tokens	*command;

	command = (t_tokens *)ft_calloc(1, sizeof(t_tokens));
	if (!command)
		return (NULL);
	command -> value = ft_strdup(cmnd);
	if (!command->value)
		return (NULL);
	command -> type = type;
	return (command);
}

t_tokens	*ft_lstlastt(t_tokens *lst)
{
	if (!lst)
		return (NULL);
	while (lst ->next)
	{
		lst = lst -> next; 
	}
	return (lst);
}

void	ft_lstadd_backk(t_tokens **lst, t_tokens *new)
{
	t_tokens	*last;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = ft_lstlastt(*lst);
	last -> next = new;
}
