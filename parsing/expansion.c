/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykamboua <ykamboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 00:15:56 by ykamboua          #+#    #+#             */
/*   Updated: 2024/11/10 03:48:02 by ykamboua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

// t_tokens	*get_env_token(t_tokens *token)
// {
// 	t_tokens	*current;
// 	char		*env;
// 	int			i;
// 	int			start;
// 	int			end;
// 	i = 0;
// 	current = token;
// 	if (token->value[0] == '$')
// 	{
// 		env = getenv(token->value + 1);
// 		token->value= env;
// 	}
// 	else if(token->type == QUOTED)
// 	{
// 		while (token->value && token->value[i])
// 		{
// 			if (token->value[i] == '$')
// 			{
// 				i++;
// 				start = i;
// 				while (!is_whitespace(token->value[i]) && token->value[i] != '"' && token->value[i])
// 					i++;
// 				end = i;
// 				env = ft_substr(token->value, start, end - start);
// 				env = getenv(env);
// 				// printf("%s\n", token->value);
// 				token->value= env;
// 				// break;
// 			}
// 			i++;
// 		}
// 	}
// 	current = current->next;
// 	return (NULL);
// }

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


// char	*get_env_token(char *token, t_ev *ev)
// {
// 	char	*str;
// 	char	*tmp;
// 	char 	*var_name;
// 	int		i, start, end;
// 	int		j;
// 	int		single_quoted;

// 	single_quoted = 0;
// 	str = ft_strdup("");
// 	i = 0;
// 	j = 0;
// 	while (token[i])//helo$USER
// 	{
// 		while ((token[i] && token[i] != '$') || single_quoted)
// 		{
// 			if(token[i] == '\'' && !single_quoted)
// 				single_quoted = 1;
// 			else if(token[i] == '\'' && single_quoted)
// 				single_quoted = 0;
// 			// tmp = str;
// 			str = ft_strjoin(str, ft_substr(token, i, 1));
// 			// printf("--%s\n", str);
// 			// free(tmp);
// 			i++;
// 		}
// 		if (token[i] == '$' && !single_quoted)
// 		{
// 			i++;
// 			if(!ft_isalpha(token[i]) || token[i] != '_')
// 			{
// 				// tmp = str;
// 				str = ft_strjoin(str, "$");
// 				// free(tmp);
//             }
// 				start = i;
// 				var_name = extract_var(token, &i);
// 				char *env_value;
// 				env_value= search_ev_value(var_name, ev);
// 				// printf("******0000%s\n",env_value);//---------------------
// 				if (!env_value)
// 				{
// 					env_value = "";
// 				}
// 				// tmp = str;
// 				str = ft_strjoin(str, env_value);
// 			// free(tmp);
//  			free(var_name);
// 		}
// 		// i++;
// 	}
// 	// printf("0---%s\n", str);
// 	return(str);
// }


char	*get_env_token(char *token, t_ev *ev)
{
	char	*str;
	char	*tmp;
	char 	*var_name;
	int		i, start, end;
	int		j;
	int		single_quoted;
	int		double_quoted;

	single_quoted = 0;
	double_quoted = 0;
	str = ft_strdup("");
	i = 0;
	j = 0;

	while (token[i]) //helo$USER
	{
	
		if(token[i] == '\"' && !double_quoted)
		{
			double_quoted = 1;
			// i++;
		}
		else if(token[i] == '\"' && double_quoted)
		{
			double_quoted = 0;
			// i++;
		}
		// while ((token[i] && token[i] != '$') || single_quoted)
		// {
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
			
			// tmp = str;
			// str = ft_strjoin(str, ft_substr(token, i, 1));
			// printf("--%s\n", str);
			// free(tmp);
			// i++;
		//}
		// }
		

		if (token[i] == '$' && ((!double_quoted && !single_quoted) || (double_quoted && single_quoted) || double_quoted))
		{
			i++;
			if(ft_isalpha(token[i]) || token[i] == '_')
			{
				// tmp = str;
				// str = ft_strjoin(str, "$");
				// free(tmp);
				// start = i;
				var_name = extract_var(token, &i);
				char *env_value;
				env_value= search_ev_value(var_name, ev);
				//---------------------
				if (!env_value)
				{
					env_value = "";
				}
				printf("******0000%s\n",env_value);
				tmp = str;
				str = ft_strjoin(str, env_value);
				free(tmp);
				free(var_name);
			}
		}
		// i++;
		else 
		{
			tmp = str;
			str = ft_strjoin(str, ft_substr(token, i, 1));
			// printf("--%s\n", str);
			free(tmp);
			i++;
		}
	
		
	}
	// printf("0---%s\n", str);
	return(str);
}


void	expand_env(t_tokens *tokens, t_ev *ev)
{
	while (tokens)
	{
		if(tokens->type == WORD)
		{
			tokens->value = get_env_token(tokens->value, ev);
		}
		tokens = tokens->next;
	}
}

// int main()
// {
// 	t_tokens *new;
// 	new = ft_lstneww("echo",0);
// 	t_tokens *new1;
// 	char *var;

// 	var = "$USER";
// 	new1 = ft_lstneww(var,0);
// 	t_tokens *new2;
// 	new2 = ft_lstneww("$USER",0);
// 	ft_lstadd_backk(&new, new1);
// 	ft_lstadd_backk(&new, new2);
// 	// printf("%s\n", expand_env(new)->value);
// 	expand_env((new));
// 	while (new)
// 	{
// 		printf("%s\n", new->value);
// 		new = new->next;
// 	}
	
// }


