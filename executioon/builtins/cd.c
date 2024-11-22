/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cahaik <cahaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 09:34:25 by cahaik            #+#    #+#             */
/*   Updated: 2024/11/22 06:04:24 by cahaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	setter(char *cwd, t_ev **ev, char *arg)
{
	t_ev	*env;
	char	*equal;

	env = *ev;
	equal = NULL;
	while ((*ev))
	{
		if (ft_strcmp((*ev)->name, "OLDPWD") == 0)
		{
			(*ev)->value = cwd;
			equal = ft_strjoin((*ev)->name, "=");
			(*ev)->line = ft_strjoin(equal, (*ev)->value);
			free(equal);
		}
		if (ft_strcmp((*ev)->name, "PWD") == 0)
		{
			(*ev)->value = arg;
			equal = ft_strjoin((*ev)->name, "=");
			(*ev)->line = ft_strjoin(equal, (*ev)->value);
			free(equal);
		}
		(*ev) = (*ev)->next;
	}
	(*ev) = env;
}

int	getter(t_ev *env, char *arg, t_ev **ev, t_status **p)
{
	char	*cwd;
	char	*cwd2;
	t_ev	**evv;

	evv = ev;
	cwd2 = NULL;
	cwd = getcwd(NULL, 0);
	if (ft_strcmp(arg, "HOME") == 0)
	{
		while (env)
		{
			if (ft_strcmp(env->name, "HOME") == 0)
			{
				arg = env->value;
				break ;
			}
			env = env->next;
		}
	}
	if (chdir(arg) == -1)
		return (free(cwd), perror_(arg, p), (*p)->exit_status);
	cwd2 = getcwd(NULL, 0);
	setter(cwd, ev, cwd2);
	(*p)->exit_status = 0;
	return (free(cwd2), free(cwd), (*p)->exit_status);
}

void	cd_(t_ev **ev, char *arg, t_status **p)
{
	t_ev	*env;

	env = *ev;
	if (arg == NULL || ft_strcmp(arg, "~") == 0)
		getter(env, "HOME", ev, p);
	else if (arg[0] != '\0')
		getter(env, arg, ev, p);
	ev = &env;
}
