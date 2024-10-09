/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cahaik <cahaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 13:22:07 by cahaik            #+#    #+#             */
/*   Updated: 2024/10/09 05:54:49 by cahaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstdelone_unset(t_ev *lst)
{
	if (!lst)
		return ;
	free(lst->line);
	free(lst->name);
	free(lst->value);
	free(lst);
}

void unset_helper(t_ev **ev, char *name)
{
	t_ev *backup;
	t_ev *prev;
	t_ev *move;

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
	
	
	0
}

void unset_(t_ev **ev, char **name)
{
	int i;

	i = 0;
	while(name && name[i]) 
	{
		unset_helper(ev, name[i]);
		i++;	
	}
}

// int main(int ac, char **av, char **env)
// {
// 	t_ev *ev;
// 	char **name;

// 	ev = environ(env);
// 	name = malloc(sizeof(char *) * 3);

// 	name[0]= "TERM";
// 	name[1]= "_";
// 	name[2] = "MallocNanoZone";
// 	unset_(&ev, name);
// 	env_(ev);
// 	return (0);
// }
