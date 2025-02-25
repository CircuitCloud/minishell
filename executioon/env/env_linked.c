/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_linked.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cahaik <cahaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 10:50:40 by cahaik            #+#    #+#             */
/*   Updated: 2024/11/28 23:42:06 by cahaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_ev	*ft_lst_new_env(char *line, char *name, char *value)
{
	t_ev	*new;

	new = (t_ev *)malloc(sizeof(t_ev));
	if (!new)
	{
		if (line)
			free(line);
		if (name)
			free(name);
		if (value)
			free(value);
		return (NULL);
	}
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

int	create_struct(char *env, t_ev **ev)
{
	size_t	len;
	t_ev	*tmp;
	char	*valuue;

	len = 0;
	tmp = NULL;
	valuue = NULL;
	valuue = ft_strdup(ft_strchr(env, '=') + 1);
	len = ft_strlen(env) - ft_strlen(valuue) - 1;
	tmp = ft_lst_new_env(ft_strdup(env), ft_substr(env, 0, len), valuue);
	if (!tmp)
		return (1);
	ft_lstadd_back_env(ev, tmp);
	return (0);
}

t_ev	*environ(char **env)
{
	int		i;
	int		tmp;
	t_ev	*ev;

	i = 0;
	ev = NULL;
	tmp = 0;
	while (env && env[i])
	{
		tmp = create_struct(env[i], &ev);
		if (tmp == 1)
		{
			write(2, "minishell : failed to allocate\n", 31);
			free_env(ev);
			exit (1);
		}
		i++;
	}
	return (ev);
}
