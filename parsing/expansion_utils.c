/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykamboua <ykamboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 10:50:40 by cahaik            #+#    #+#             */
/*   Updated: 2024/11/26 11:18:30 by ykamboua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*search_ev_value(char *exp_name, t_ev *env)
{
	t_ev	*current;

	current = env;
	while (current)
	{
		if (ft_strncmp(exp_name, current->name, ft_strlen(exp_name) + 1) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

char	*extract_var(char *str, int *pos)
{
	int	start;

	start = *pos;
	while (str[*pos] && (ft_isalpha(str[*pos]) || 
			ft_isalnum(str[*pos]) || 
			str[*pos] == '_') && !is_whitespace(str[*pos]))
	{
		(*pos)++;
	}
	return (ft_substr(str, start, *pos - start));
}

char	*safe_ft_strjoin(char *s1, char *s2, int flag)
{
	char	*result;

	result = ft_strjoin(s1, s2);
	if (!result)
	{
		if (s1)
			free(s1);
		if (flag && s2)
			free(s2);
		return (NULL);
	}
	if (s1)
	{
		free(s1);
		s1 = NULL;
	}
	if (flag && s2)
	{
		free(s2);
		s2 = NULL;
	}
	return (result);
}

void	free_token(char **token)
{
	if (*token)
	{
		free(*token);
		*token = NULL;
	}
}
