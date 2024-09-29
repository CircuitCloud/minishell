/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykamboua <ykamboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 21:46:23 by ykamboua          #+#    #+#             */
/*   Updated: 2024/09/29 03:23:17 by ykamboua         ###   ########.fr       */
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
//     t_command cmd;
//     cmd.tokens_list = NULL; 
//     char *token1 = "echo";
//     char *token2 = "hello";
//     char *token3 = "world";
//     t_tokens *t1 = ft_lstneww(token1, 0);
//     t_tokens *t2 = ft_lstneww(token2, 0);
//     t_tokens *t3 = ft_lstneww(token3, 0);
//     ft_lstadd_backk(&(cmd.tokens_list), t1);
//     ft_lstadd_backk(&(cmd.tokens_list), t2);
//     ft_lstadd_backk(&(cmd.tokens_list), t3);
//     t_tokens *current = cmd.tokens_list;
//     while (current)
//     {
//         printf("Token: %s\n", current->value);
//         current = current->next;
//     }

//     return 0;
// }
