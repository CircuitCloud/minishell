/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cahaik <cahaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 09:34:25 by cahaik            #+#    #+#             */
/*   Updated: 2024/11/27 00:07:01 by cahaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	setter_getter_helper(t_ev *ev, char **arg, int c)
{
	if (c == 0)
	{
		if (ev->value)
			free(ev->value);
		if (ev->line)
			free(ev->line);
	}
	else
	{
		if (ft_strcmp(ev->name, "HOME") == 0)
		{
			(*arg) = ev->value;
			return (1);
		}
	}
	return (0);
}

void	setter(char *cwd, t_ev **ev, char *arg)
{
	t_ev	*env;
	char	*equal;

	env = *ev;
	while ((*ev))
	{
		if (ft_strcmp((*ev)->name, "OLDPWD") == 0)
		{
			setter_getter_helper((*ev), NULL, 0);
			(*ev)->value = ft_strdup(cwd);
			equal = ft_strjoin((*ev)->name, "=");
			(*ev)->line = ft_strjoin(equal, (*ev)->value);
			free(equal);
		}
		if (ft_strcmp((*ev)->name, "PWD") == 0)
		{
			setter_getter_helper((*ev), NULL, 0);
			(*ev)->value = ft_strdup(arg);
			equal = ft_strjoin((*ev)->name, "=");
			(*ev)->line = ft_strjoin(equal, (*ev)->value);
			free(equal);
		}
		(*ev) = (*ev)->next;
	}
	(*ev) = env;
}

int	getter(t_ev *env, char *arg, t_ev **ev, t_status *p)
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
			if (setter_getter_helper(env, &arg, 1) == 1)
				break ;
			env = env->next;
		}
	}
	if (ft_strcmp(arg, "HOME") == 0)
		return (free(cwd), write (2, "minishell: cd: HOME not set\n", 28),
			p->exit_status);
	if (chdir(arg) == -1)
		return (free(cwd), perror_(arg, p), p->exit_status);
	cwd2 = getcwd(NULL, 0);
	setter(cwd, ev, cwd2);
	p->exit_status = 0;
	return (free(cwd2), free(cwd), p->exit_status);
}

void	cd_(t_ev **ev, char *arg, t_status *p)
{
	t_ev	*env;

	env = *ev;
	if (arg == NULL || ft_strcmp(arg, "~") == 0)
		getter(env, "HOME", ev, p);
	else if (arg[0] != '\0')
		getter(env, arg, ev, p);
	ev = &env;
}
