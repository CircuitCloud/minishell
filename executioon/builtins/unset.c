/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cahaik <cahaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 13:22:07 by cahaik            #+#    #+#             */
/*   Updated: 2024/11/23 05:34:12 by cahaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_lstdelone_unset(t_ev *lst)
{
	if (!lst)
		return ;
	if (lst->line)
		free(lst->line);
	if (lst->name)
		free(lst->name);
	if (lst->value)
		free(lst->value);
	if (lst)
		free(lst);
}

int	is_alphabet(char *arg)
{
	int	i;

	i = 0;
	while (i < ft_strlen(arg))
	{
		if (i == 0 && (ft_isalpha(arg[i]) != 1 && arg[i] != '_'))
			return (1);
		if (ft_isalpha(arg[i]) != 1 && ft_isdigit(arg[i]) != 1 
			&& arg[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

void	unset_helper(t_ev **ev, char *name)
{
	t_ev	*backup;
	t_ev	*prev;
	t_ev	*move;

	move = *ev;
	while (move && name)
	{
		if (ft_strcmp(move->name, name) == 0)
		{
			backup = move;
			if (*ev == move)
				*ev = (*ev)->next;
			else
				prev->next = backup->next;
			ft_lstdelone_unset(backup);
			break ;
		}
		prev = move;
		move = move->next;
	}
	return ;
}

void	unset_(t_ev **ev, char **name, t_status **p)
{
	int	i;

	i = 0;
	while (name && name[i]) 
	{
		if (is_alphabet(name[i]) != 1)
			unset_helper(ev, name[i]);
		else
		{
			write(2, "minishell: unset: ", 18);
			write(2, name[i], ft_strlen(name[i]));
			write(2, ": not a valid identifier\n", 26);
			(*p)->exit_status = 0;
		}
		i++;
	}
}
