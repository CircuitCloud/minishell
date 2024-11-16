/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cahaik <cahaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 00:15:56 by ykamboua          #+#    #+#             */
/*   Updated: 2024/11/16 05:06:32 by cahaik           ###   ########.fr       */
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
	char	*var_name;
	int		i, start;
	int		single_quoted = 0;
	int		double_quoted = 0;
	char	*env_value;

	str = ft_strdup("");
	i = 0;

	while (token[i])
	{
		if (token[i] == '\'' && !double_quoted)
		{
			single_quoted = !single_quoted;
			str = ft_strjoin(str, "'"); 
			i++;
			while (token[i] && single_quoted)
			{
				if (token[i] == '\'')
				{
					single_quoted = !single_quoted;
					str = ft_strjoin(str, "'"); 
					i++;
					break;
				}
				str = ft_strjoin(str, ft_substr(token, i, 1));
				i++;
			}
			////ctttttt 
		}
		if (token[i] == '"' && !single_quoted)
		{
			double_quoted = !double_quoted;
			str = ft_strjoin(str, "\"");
			i++;
			while (token[i] && double_quoted)
			{
				if (token[i] == '"')
				{
					double_quoted = !double_quoted;
					str = ft_strjoin(str, "\"");
					i++;
					break;
				}
				if (token[i] == '$')
				{
					i++;
					if (ft_isdigit(token[i]))
					{
						i++;
					}
					else if (ft_isalpha(token[i]))
					{
						var_name = extract_var(token, &i);
						env_value = search_ev_value(var_name, ev);
						if (!env_value)
							env_value = "";
						str = ft_strjoin(str, env_value);
						free(var_name);
					}
					else if (token[i] == '?')
					{
						str = ft_strjoin(str, ft_itoa((*p)->exit_status));
						i++;
					}
				}
				else
				{
					str = ft_strjoin(str, ft_substr(token, i, 1));
					i++;
				}
			}
		//ctttttt
		}

		if (token[i] == '$' && !single_quoted)
		{
			i++;
			if (ft_isdigit(token[i]))
			{
				i++;
			}
			else if (ft_isalpha(token[i]) || token[i] == '_')
			{
				var_name = extract_var(token, &i);
				env_value = search_ev_value(var_name, ev);
				if (!env_value)
					env_value = "";
				str = ft_strjoin(str, env_value);
				free(var_name);
			}
			else if (token[i] == '?')
			{
				str = ft_strjoin(str, ft_itoa((*p)->exit_status));
				i++;
			}
			////ctttttt
		}

		start = i;
		while (token[i] && token[i] != '$' && token[i] != '\'' && token[i] != '"')
			i++;
		if (i > start)
			str = ft_strjoin(str, ft_substr(token, start, i - start));
	}

	return (str);
}

//--------------------------------
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

