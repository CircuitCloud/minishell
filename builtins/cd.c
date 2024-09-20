/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cahaik <cahaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 09:34:25 by cahaik            #+#    #+#             */
/*   Updated: 2024/09/20 09:30:41 by cahaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void setter(char *cwd, t_ev *env, t_ev **ev, char *arg)
{
	char *equal;

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
		else if (ft_strcmp((*ev)->name, "PWD") == 0)
		{
			(*ev)->value = arg;
			equal = ft_strjoin((*ev)->name, "=");
			(*ev)->line = ft_strjoin(equal, (*ev)->value);
			free(equal);
		}
		(*ev) = (*ev)->next;
	}
}

int getter(t_ev *env, char *arg, t_ev **ev)
{
	char *cwd;
	
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
	if (chdir(arg) != -1)
		setter(cwd, env, ev, getcwd(NULL, 0));
	else
	{
		perror("chdir");
		return (1);
	}
	return (0);
}

int cd_(t_ev **ev, char *arg)
{
	int i;
	t_ev *env;

	env = *ev;
	if (arg == NULL || ft_strcmp(arg, "~") == 0)
		return (getter(env, "HOME", ev));
	else if (arg[0] != '\0')
			return (getter(env, arg, ev));
	return (0);
}

// int main(int ac, char **av, char ** env)
// {
// 	char **arg;
// 	int i;
// 	t_ev *ev;
// 	t_ev *ennv;
	
// 	i = 0;
// 	ev = environ(env);
// 	ennv = ev;
// 	cd_(&ennv , av[1]);
// 	// printf("%s\n", getcwd(NULL, 0));
// 	env_(ev);
	
// 	return (0);
// }