/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykamboua <ykamboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 00:15:56 by ykamboua          #+#    #+#             */
/*   Updated: 2024/10/11 00:21:09 by ykamboua         ###   ########.fr       */
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





void	expand_env(t_tokens *tokens)
{
	while (tokens)
	{
		get_env_token(tokens);
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