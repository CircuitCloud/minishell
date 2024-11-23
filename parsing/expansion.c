/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykamboua <ykamboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 00:15:56 by ykamboua          #+#    #+#             */
/*   Updated: 2024/11/23 01:34:38 by ykamboua         ###   ########.fr       */
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
char	*safe_ft_strjoin(char *s1, char *s2, int flag)
{
    char *result = ft_strjoin(s1, s2);

    if (!result)
    {
		if(s1)
		{
        	free(s1);
			s1 = NULL;
		}
		if(flag && s2)
		{
			free(s2);
			s2 = NULL;
		}
        return (NULL);
    }
	if(s1)
	{
    	free(s1);
		s1 = NULL;
	}
	if(flag && s2)
	{
		free(s2);
		s2 = NULL;
	}
    return (result);
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
			str = safe_ft_strjoin(str, "'", 0); 
			i++;
			while (token[i] && single_quoted)
			{
				if (token[i] == '\'')
				{
					single_quoted = !single_quoted;
					str = safe_ft_strjoin(str, "'", 0); 
					i++;
					break;
				}
				str = safe_ft_strjoin(str, ft_substr(token, i, 1), 1);
				i++;
			}
			////ctttttt 
		}
		if (token[i] == '"' && !single_quoted)
		{
			double_quoted = !double_quoted;
			str = safe_ft_strjoin(str, "\"", 0);
			i++;
			while (token[i] && double_quoted)
			{
				if (token[i] == '"')
				{
					double_quoted = !double_quoted;
					str = safe_ft_strjoin(str, "\"", 0);
					i++;
					break;
				}
				if (token[i] == '$')
				{
					i++;
					if(token[i] == '"' || is_whitespace(token[i]))
					{
						str = safe_ft_strjoin(str, "$", 0);
						i++;
					}
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
						str = safe_ft_strjoin(str, ft_strdup(env_value), 1);
						free(var_name);
					}
					else if (token[i] == '?')
					{
						str = safe_ft_strjoin(str, ft_itoa((*p)->exit_status), 1);
						i++;
					}
				}
				else
				{
					
					str = safe_ft_strjoin(str, ft_substr(token, i, 1), 1);
					i++;
				}
			}
		//ctttttt
		}

		if (token[i] == '$' && !single_quoted)
		{
			i++;
			if(!token[i])
			{
				str = safe_ft_strjoin(str, "$", 0);
			}
			if (ft_isdigit(token[i]))
			{
				i++;
			}
			else if (ft_isalpha(token[i]) || token[i] == '_')
			{
				var_name = extract_var(token, &i);
				// dprintf(2, ">>>>{%s}\n" ,var_name + 16);
				env_value = search_ev_value(var_name, ev);
				if (!env_value)
					env_value = "";
				str = safe_ft_strjoin(str,  ft_strdup(env_value), 1);
				free(var_name);
				var_name = NULL;
				// free(env_value);
			}
			else if (token[i] == '?')
			{
				str = safe_ft_strjoin(str, ft_itoa((*p)->exit_status), 1);
				i++;
			}
			////ctttttt
		}
		start = i;
		while (token[i] && token[i] != '$' && token[i] != '\'' && token[i] != '"')
			i++;
		if (i > start)
		{
			str = safe_ft_strjoin(str, ft_substr(token, start, i - start), 1);
		}
			
	}
	if(token)
	{
		free(token);
		token = NULL;
	}
	return (str);
}

//--------------------------------
void	expand_env(t_tokens *tokens, t_ev *ev, t_status *p)
{
	while (tokens)
	{
		if(tokens->type == HERDOC)
		{
			if(tokens->next && (tokens->next->value[0] == '\'' || tokens->next->value[0] == '"'))
				tokens->hdoc_expand = 0;
			else
				tokens->hdoc_expand = 1;
				// printf("%d\n", redir->hdoc_need_expand);
		}
		if(tokens->type == WORD)
		{
			tokens->value = get_env_token(tokens->value, ev, &p);
		}
		tokens = tokens->next;
	}
}


