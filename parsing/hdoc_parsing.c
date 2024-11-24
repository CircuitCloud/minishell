/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdoc_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykamboua <ykamboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 01:15:37 by ykamboua          #+#    #+#             */
/*   Updated: 2024/11/24 09:25:14 by ykamboua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../minishell.h"


char	*hdoc_expand_handler(char *token, t_ev *ev, t_status **p)
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
		if (token[i] == '$' )
		{
			i++;
			if(!token[i])
			{
				str = safe_ft_strjoin(str, "$", 0);
			}
			if (ft_isdigit(token[i]))
				i++;
			else if (ft_isalpha(token[i]) || token[i] == '_')
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
		start = i;
		while (token[i] && token[i] != '$')
			i++;
		if (i > start)
			str = safe_ft_strjoin(str, ft_substr(token, start, i - start), 1);
	}
	return (str);
}
