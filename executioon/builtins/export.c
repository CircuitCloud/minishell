/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cahaik <cahaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 09:35:30 by cahaik            #+#    #+#             */
/*   Updated: 2024/11/27 00:07:57 by cahaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	value_helper(char **value, char *arg, char c)
{
	if (c == '=')
		*value = ft_strdup(ft_strchr(arg, c) + 1);
	else if (c == '+')
		*value = ft_strdup(ft_strchr(arg, c) + 2);
	else
		*value = NULL;
}

void	fill_lv_export(t_ev **move, char *value, char *arg, int c)
{
	char	*tmp[2];

	if (!value)
		return ;
	tmp[0] = (*move)->line;
	tmp[1] = (*move)->value;
	if (c == '=')
	{
		(*move)->line = ft_strdup(arg);
		(*move)->value = ft_strdup(value);
	}
	else
	{
		(*move)->line = ft_strjoin((*move)->line, value);
		(*move)->value = ft_strjoin((*move)->value, value);
	}
	free(tmp[0]);
	free(tmp[1]);
	free(value);
	return ;
}

int	export_helper(char *arg, t_ev **ev, char c)
{
	char	*name;
	char	*value;
	char	*tmp;
	t_ev	*move;

	move = *ev;
	name = ft_substr(arg, 0, ft_strlen(arg) - ft_strlen(ft_strchr(arg, c)));
	value_helper(&value, arg, c);
	while (move)
	{
		if (ft_strcmp(move->name, name) == 0)
			return (fill_lv_export(&move, value, arg, c), free(name), 0);
		move = move->next;
	}
	if (value)
	{
		tmp = ft_strjoin(name, "=");
		ft_lstadd_back_env(ev, ft_lst_new_env(ft_strjoin(tmp, value), 
				name, value));
		free(tmp);
	}
	else
		ft_lstadd_back_env(ev, ft_lst_new_env(ft_strdup(name), name, NULL));
	return (0);
}

void	export_no_arg(t_ev *ev)
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

void	export_(char **args, t_ev **ev, t_status *p)
{
	int	i;

	i = 0;
	if (args && !args[0])
	{
		export_no_arg(*ev);
		return ;
	}
	while (args[i])
	{
		if (valide_var(args[i]) == 1)
		{
			write(2, "minishell: export: ", 19);
			write(2, args[i], ft_strlen(args[i]));
			write(2, " : not a valid identifier\n", 27);
			p->exit_status = 1;
		}
		else if (valide_var(args[i]) == 0)
			export_helper(args[i], ev, '+');
		else if (valide_var(args[i]) == 2)
			export_helper(args[i], ev, '=');
		else
			export_helper(args[i], ev, 'n');
		i++;
	}
}
