/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_op.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykamboua <ykamboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 10:46:15 by ykamboua          #+#    #+#             */
/*   Updated: 2024/11/26 11:55:07 by ykamboua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	expand_single_quotes(t_expand_data *expand_data)
{
	expand_data->single_quoted = !expand_data->single_quoted;
	expand_data->str = safe_ft_strjoin(expand_data->str, "'", 0); 
	(expand_data->i)++;
	while (expand_data->token[expand_data->i] && expand_data->single_quoted)
	{
		if (expand_data->token[expand_data->i] == '\'')
		{
			expand_data->single_quoted = !expand_data->single_quoted;
			expand_data->str = safe_ft_strjoin(expand_data->str, "'", 0); 
			(expand_data->i)++;
			break ;
		}
		expand_data->str = safe_ft_strjoin(expand_data->str, 
				ft_substr(expand_data->token, expand_data->i, 1), 1);
		(expand_data->i)++;
	}
}

void	exp_d_quotes(t_expand_data *exp, t_ev *ev, t_status **p)
{
	char	*var_name;
	char	*env_value;

	(exp->i)++;
	if (exp->token[exp->i] == '"' || is_whitespace(exp->token[exp->i]))
	{
		exp->str = safe_ft_strjoin(exp->str, "$", 0);
		exp->i++;
	}
	if (ft_isdigit(exp->token[exp->i]))
		exp->i++;
	else if (ft_isalpha(exp->token[exp->i]))
	{
		var_name = extract_var(exp->token, &exp->i);
		env_value = search_ev_value(var_name, ev);
		if (!env_value)
			env_value = "";
		exp->str = safe_ft_strjoin(exp->str, ft_strdup(env_value), 1);
		free(var_name);
	}
	else if (exp->token[exp->i] == '?')
	{
		exp->str = safe_ft_strjoin(exp->str, ft_itoa((*p)->exit_status), 1);
		(exp->i)++;
	}
}

void	expand_double_quotes(t_expand_data *expand_data, t_ev *ev, t_status **p)
{
	expand_data->double_quoted = !expand_data->double_quoted;
	expand_data->str = safe_ft_strjoin(expand_data->str, "\"", 0);
	(expand_data->i)++;
	while (expand_data->token[expand_data->i] && expand_data->double_quoted)
	{
		if (expand_data->token[expand_data->i] == '"')
		{
			expand_data->double_quoted = !expand_data->double_quoted;
			expand_data->str = safe_ft_strjoin(expand_data->str, "\"", 0);
			(expand_data->i)++;
			break ;
		}
		if (expand_data->token[expand_data->i] == '$')
			exp_d_quotes(expand_data, ev, p);
		else
		{
			expand_data->str = safe_ft_strjoin(expand_data->str, 
					ft_substr(expand_data->token, expand_data->i, 1), 1);
			(expand_data->i)++;
		}
	}
}

void	expd_no_quoted_word(t_expand_data *exp, t_ev *ev, t_status **p)
{
	char	*var_name;
	char	*env_value;

	(exp->i)++;
	if (!exp->token[exp->i])
		exp->str = safe_ft_strjoin(exp->str, "$", 0);
	if (ft_isdigit(exp->token[exp->i]))
		(exp->i)++;
	else if (ft_isalpha(exp->token[exp->i]) 
		|| exp->token[exp->i] == '_')
	{
		var_name = extract_var(exp->token, &exp->i);
		env_value = search_ev_value(var_name, ev);
		if (!env_value)
			env_value = "";
		exp->str = safe_ft_strjoin(exp->str, ft_strdup(env_value), 1);
		free(var_name);
		var_name = NULL;
	}
	else if (exp->token[exp->i] == '?')
	{
		exp->str = safe_ft_strjoin(exp->str, ft_itoa((*p)->exit_status), 1);
		(exp->i)++;
	}
}
