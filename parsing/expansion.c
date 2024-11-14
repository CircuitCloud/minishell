/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykamboua <ykamboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 00:15:56 by ykamboua          #+#    #+#             */
/*   Updated: 2024/11/14 22:07:15 by ykamboua         ###   ########.fr       */
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



// char	*get_env_token(char *token, t_ev *ev, t_status **p)
// {
// 	int	i;
// 	char 	*var_name;
// 	char 	*env_value;
// 	char	*expanded_res;
// 	char	*start;
// 	char	*tmp;

// 	i = 0;
// 	expanded_res =  ft_strdup("");
// 	while (token[i])
// 	{
// 		if (token[i] == '$' && ft_isdigit(token[i] + 1))
// 		{
// 			i++;
// 			tmp = extract_var(token, &i);
// 			printf("%s\n", tmp);
// 			expanded_res = ft_strjoin(expanded_res, tmp);
// 		}
// 		// if (token[i] == '$')
// 		// {
// 		// 	var_name = extract_var(token, &i);
// 		// 	env_value = search_ev_value(var_name, ev);
// 		// 	if(!env_value)
// 		// 		env_value = ft_strdup("");
// 		// }
// 		i++;
// 	}
// 	return(expanded_res);
// }



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
		if(token[i] == '\'' && !double_quoted)
		{
			single_quoted = !single_quoted;
			i++;
			continue;
		}
		if(token[i] == '"' && !single_quoted)
		{
			double_quoted = !double_quoted;
			i++;
			continue;

		}
		start = i;
		while (token[i] && token[i] != '$')
		{
			i++;
		}
		if (i > start)
		{
			str = ft_strjoin(str, ft_substr(token, start, i - start));
			// printf("...%s\n", str);
		}
		if (token[i] == '$' && !single_quoted)
		{
			i++;
			if(ft_isdigit(token[i]))
			{
				i++;
			}
			else if(ft_isalpha(token[i]))
			{
				var_name = extract_var(token, &i);
				env_value= search_ev_value(var_name, ev);
				if (!env_value)
					env_value = "";
				str = ft_strjoin(str, env_value);
				free(var_name);
			}
			else if (token[i] && token[i] == '?')
			{
				// printf("kkkiko\n");
				str = ft_strjoin(str, ft_itoa(((*p)->exit_status)));
				i++;
			}
		}
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

