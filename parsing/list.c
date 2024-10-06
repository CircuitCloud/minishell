/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykamboua <ykamboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 21:46:23 by ykamboua          #+#    #+#             */
/*   Updated: 2024/10/03 01:40:03 by ykamboua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_tokens	*ft_lstneww(char *cmnd, int type)
{
	t_tokens	*command;

	command = (t_tokens *)malloc(sizeof(t_tokens));
	if (!command)
		return (NULL);
	command -> value = ft_strdup(cmnd);;
	command -> type = type;
	command -> next = NULL;
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

	if (!lst)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = ft_lstlastt(*lst);
	last -> next = new;
}

// int main()
// {
// 	t_tokens *token;
// 	t_tokens *token1;
// 	t_tokens *token2;
// 	t_tokens *token3;
// 	t_tokens *current;
	
// 	token = ft_lstneww("hello ", 0);
// 	token1 = ft_lstneww("ya  ", 0);
// 	token2= ft_lstneww("a ", 0);
// 	token3 = ft_lstneww("smitq ", 0);

// 	ft_lstadd_backk(&(token), token1);
// 	ft_lstadd_backk(&(token1), token2);
// 	ft_lstadd_backk(&(token2), token3);

// 	current = token;
// 	while (current)
// 	{
// 		printf("%s\n", current->value);
// 		current = current->next;
// 	}
	
// }