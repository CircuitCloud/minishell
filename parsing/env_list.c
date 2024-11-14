/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykamboua <ykamboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 10:50:40 by cahaik            #+#    #+#             */
/*   Updated: 2024/11/14 20:04:56 by ykamboua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*search_ev_value(char *exp_name, t_ev *env)
{
	t_ev	*current;

	current = env;
	// printf("-----%s\n", env->value);
	while (current)
	{
		// printf("search ev    %s\n", current->line);
		if(ft_strncmp(exp_name, current->name, ft_strlen(exp_name) + 1) == 0)
		{
			// printf("---zz%s\n", current->value);
			return(current->value);
		}
		current = current->next;
	}
	return(NULL);
}