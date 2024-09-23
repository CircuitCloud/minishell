/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cahaik <cahaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 09:35:30 by cahaik            #+#    #+#             */
/*   Updated: 2024/09/23 19:10:04 by cahaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int valide_var(char *arg)
{
	int i;

	i = 0;
	while (arg[i])
	{
		if (i == 0 && ft_isalpha(arg[i]) != 1)
			return (1) ;
		else if (i != 0 && arg[i] == '+' && arg[i + 1] == '=')
			return (0);
		else if (i != 0 && arg[i] == '=')
			return (2);
		else if (ft_isalpha(arg[i]) != 1 && ft_isdigit(arg[i]) != 1 
			&& arg[i] != '_')
			return (1) ;
		i++;
	}
	return (3);
}
void export_helper(char *arg, t_ev **ev, char c)
{
	char *name;
	char *value;
	char *tmp;
	t_ev *move;

	name = ft_substr(arg, 0, ft_strlen(arg) - ft_strlen(ft_strchr(arg, c)));
	move = *ev;
	if (c == '=')
		value = ft_strchr(arg, c) + 1;
	else if (c == '+')
		value = ft_strchr(arg, c) + 2;
	else
		value = NULL;
	while (move)
	{
		if(ft_strcmp(move->name, name) == 0)
		{
			if (!value)
				return ;
			if (c == '=')
			{
				move->line = ft_strdup(arg);
				move->value = ft_strdup(value);
			}
			else
			{
				move->line = ft_strjoin(move->line, value);
				move->value = ft_strjoin(move->value, value);
			}
			return;
		}
		move = move->next;
	}
	if (value)
	{
		tmp = ft_strjoin(name, "=");
		ft_lstadd_back_env(ev, ft_lst_new_env(ft_strjoin(tmp, value), name, value));
		free(tmp);
	}
	else
		ft_lstadd_back_env(ev, ft_lst_new_env(name, name, NULL));
}

void export_no_arg(t_ev *ev)
{
	while (ev)
	{
		if (ev->value)
			printf("declare -x %s=\"%s\"\n", ev->name, ev->value);
		else
			printf("declare -x %s\n", ev->line);
		ev = ev->next;
	}
}

int export_(char **args, t_ev **ev)
{
	int i = 0;
	
	if (!args[i])
		return (export_no_arg(*ev), 0);
	while (args[i])
	{
		if (valide_var(args[i]) == 1)
				printf("minishell: export: `%s': not a valid identifier\n", args[i]);
		else if (valide_var(args[i]) == 0)
			export_helper(args[i], ev, '+');
		else if (valide_var(args[i]) == 2)
			export_helper(args[i], ev, '=');
		else
			export_helper(args[i], ev, 'n');
		i++;
	}
	return (0);	
}

// int main(int ac, char **av, char **env)
// {
// 	int i = 0;
// 	t_ev *ev;
// 	char **args;
// 	t_ev *ennv;
	
// 	args = malloc(sizeof(char *) * ac);
// 	if (!args)
// 		return (1);
// 	while(i < ac - 1)
// 	{
// 		args[i] = av[i + 1];
// 		i++;
// 	}
// 	args[i] = NULL;
// 	ev = environ(env);
// 	ennv = ev;
// 	export_(args, &ev);
// 	// env_(ennv);
// 	export_no_arg(ennv);
// 	return (0);
// }
