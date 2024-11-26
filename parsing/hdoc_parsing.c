/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdoc_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykamboua <ykamboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 01:15:37 by ykamboua          #+#    #+#             */
/*   Updated: 2024/11/26 11:34:16 by ykamboua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	hdoc_expand2(t_expand_data *expand_data, t_ev *ev, t_status **p)
{
	char	*var_name;
	char	*env_value;

	expand_data->i++;
	if (!expand_data->token[expand_data->i])
		expand_data->str = safe_ft_strjoin(expand_data->str, "$", 0);
	if (ft_isdigit(expand_data->token[expand_data->i]))
		expand_data->i++;
	else if (ft_isalpha(expand_data->token[expand_data->i]) 
		|| expand_data->token[expand_data->i] == '_')
	{
		var_name = extract_var(expand_data->token, &expand_data->i);
		env_value = search_ev_value(var_name, ev);
		if (!env_value)
			env_value = "";
		expand_data->str = safe_ft_strjoin(expand_data->str, 
				ft_strdup(env_value), 1);
		free(var_name);
	}
	else if (expand_data->token[expand_data->i] == '?')
	{
		expand_data->str = safe_ft_strjoin(expand_data->str, 
				ft_itoa((*p)->exit_status), 1);
		expand_data->i++;
	}
}

char	*hdoc_expand(char *token, t_ev *ev, t_status **p)
{
	t_expand_data	expand_data;

	expand_data.token = token;
	expand_data.str = ft_strdup("");
	expand_data.i = 0;
	while (expand_data.token[expand_data.i])
	{
		if (expand_data.token[expand_data.i] == '$' )
			hdoc_expand2(&expand_data, ev, p);
		expand_data.start = expand_data.i;
		while (expand_data.token[expand_data.i] && 
			expand_data.token[expand_data.i] != '$')
			expand_data.i++;
		if (expand_data.i > expand_data.start)
			expand_data.str = 
				safe_ft_strjoin(expand_data.str, ft_substr(token, 
						expand_data.start, expand_data.i - 
						expand_data.start), 1);
	}
	return (expand_data.str);
}
