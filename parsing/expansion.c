/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cahaik <cahaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 00:15:56 by ykamboua          #+#    #+#             */
/*   Updated: 2024/11/13 03:38:29 by cahaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"



char	*extract_var(char *str, int *pos)
{
	int	start;

	start = *pos;
	while (str[*pos] && (ft_isalpha(str[*pos]) || ft_isalnum(str[*pos]) || str[*pos] == '_') && !is_whitespace(str[*pos]) )
	{
		(*pos)++;
	}
	return(ft_substr(str, start, *pos - start));
}





char	*get_env_token(char *token, t_ev *ev, t_status **p)
{
	char	*str;
	// char	*tmp;
	char 	*var_name;
	int		i, start, end;
	int		j;
	int		single_quoted;
	int		double_quoted;
	char 	*env_value;

	single_quoted = 0;
	double_quoted = 0;
	str = ft_strdup("");
	i = 0;
	j = 0;

	while (token[i])
	{
		// if(token[i] == '\"' && !double_quoted)
		// {
		// 	double_quoted = 1;
		// 	// i++;
		// }
		// else if(token[i] == '\"' && double_quoted)
		// {
		// 	double_quoted = 0;
		// 	// i++;
		// }
		if(token[i] == '\'' && !single_quoted)
		{
			single_quoted = 1;
			// i++;
		}
		else if(token[i] == '\'' && single_quoted)
		{
			single_quoted = 0;
			// i++;
		}
		if (token[i] == '$' && !single_quoted)
		{
			i++;
			if(ft_isdigit(token[i]))
			{
				i++;
				while (!is_whitespace(token[i]))
				{
					str = ft_strjoin(str, ft_substr(token, i, 1));
					i++;
				}
			}
			if(ft_isalpha(token[i]) || token[i] == '_')
			{
				var_name = extract_var(token, &i);
				env_value= search_ev_value(var_name, ev);
				if (!env_value)
					env_value = "";
				str = ft_strjoin(str, env_value);
				free(var_name);
			}
			else if ( token[i] == '?' && !token[++i])
					str = ft_itoa(((*p)->exit_status));	
		}
		// i++;
			str = ft_strjoin(str, ft_substr(token, i, 1));
			i++;
	}
	return(str);
}


void	expand_env(t_tokens *tokens, t_ev *ev, t_status *p)
{
	while (tokens)
	{
		if(tokens->type == WORD)
		{
			tokens->value = get_env_token(tokens->value, ev, &p);
		}
		tokens = tokens->next;
	}
}

