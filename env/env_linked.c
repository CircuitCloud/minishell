/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_linked.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cahaik <cahaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 10:50:40 by cahaik            #+#    #+#             */
/*   Updated: 2024/09/15 11:51:34 by cahaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_ev	*ft_lst_new_env(char *line, char *name, char *value)
{
	t_ev	*new;

	new = (t_ev *)malloc(sizeof(t_ev));
	if (!new)
		return (NULL);
	new->line = line;
	new->name = name;
	new->value = value;
	new->next = NULL;
	return (new);
}

t_ev	*ft_lstlast_env(t_ev *lst)
{
	t_ev	*last;

	if (!lst)
		return (NULL);
	while (lst != NULL)
	{
		last = lst;
		lst = lst->next;
	}
	return (last);
}


void	ft_lstadd_back_env(t_ev **lst, t_ev *new)
{
	t_ev	*head;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		head = ft_lstlast_env(*lst);
		head->next = new;
	}
}

int environ(char **env)
{
	int i;
	t_ev *ev;
	t_ev *tmp;
	size_t len;
	char *valuue;

	i = 0;
	len = 0;
	valuue = NULL;
	while (env && env[i])
	{
		valuue = ft_strdup(ft_strchr(env[i], '=') + 1);
		len = ft_strlen(env[i]) - ft_strlen(valuue) - 1;
		tmp = ft_lst_new_env(ft_strdup(env[i]), ft_substr(env[i], 0, len), valuue);
		ft_lstadd_back_env(&ev, tmp);
		i++;
	}
	return (0);
}
