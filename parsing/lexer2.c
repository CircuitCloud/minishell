/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykamboua <ykamboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 22:27:58 by ykamboua          #+#    #+#             */
/*   Updated: 2024/10/01 23:23:37 by ykamboua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	quotes_handler(char *input, int start, char c)
{
	int i;

	i  = start;
	while (input[i])
	{
		if (input[i] == c)
			return (i);
		i++;
	}
	return (i);
}

int	words_handler(char *str, int *index)
{
	int	i;
	int	res;
	i   = *index;
	while (str[i] && str[i] != ' ')
	{
		res++;
		// if(str[index] == '\'' || str[index] == '\"')
		// 	i = quotes_handler(str, index, str[index]);
		i++;
	}
	return(i--);
}


// int	get_index_value(char *str, int start)
// {
// 	int	i;
// 	int	j;

// 	i = start;
// 	// j = 0;

// 	// while (str[i])
// 	// {
// 		if (str[i] == '\'' || str[i] == '\"')
// 		{
// 			j = quotes_handler(str, i, str[i]);
// 		}
// 		else if(!is_token(str[i]))
// 		{
// 			j = words_handler(str, i);
// 		}
// 		i = i + j;
// 	//}
// 	return (i);
// }

int is_token(char c)
{
    if (c == '|' || c == '<' || c == '>')
        return 1;
    return 0;
}

// int lexer(t_command *data)
// {
// 	t_tokens	*tok;
// 	int			i;
// 	int			j;
// 	int			type;
// 	char		*str;
// 	char		*token;
// 	t_tokens	*new_node;
// 	str = data->cmnd;
// 	tok = data -> tokens_list;
// 	i = 0;
// 	while (i < ft_strlen(str))
// 	{
// 		j = get_index_value(str, i) - 1;	
// 		// if(j >= ft_strlen(str))
// 		// 	break;
// 		token = ft_substr(str, i, j);
// 		printf("----%s\n", token);
// 		printf("%d\n", i);
// 		printf("%d\n", j);
// 		new_node = ft_lstneww(token, 0);
// 		ft_lstadd_backk(&(data->tokens_list), new_node);
// 		// else if(type == is_token(str[i]))
// 		// 	j = append_token(str, type);
// 		free(token);
// 		// free(new_node);
// 		i = i + j;
// 	}
//     return (i);
// }


int lexer(t_command *data)
{
	t_tokens	*tok;
	int			i;
	int			j;
	int			type;
	char		*str;
	char		*token;
	t_tokens	*new_node;
	str = data->cmnd;
	tok = data -> tokens_list;
	i = 0;
	
	int start ;
	start = i;
	while (str[i] && str[i] != ' ')
	{
		i++;
	}
	token = ft_substr(str, i, start - i);
    return (i);
}

// int main()
// {
// 	t_command data;
// 	char *str ;
// 	str = readline("minii>");
// 	data.cmnd= str;
	
// 	printf("%d\n",lexer(&data));
// }

#include <stdio.h>

int main()
{
    t_command data;
    t_tokens *token_node;
    char *str;

    str = readline("minii>");
    data.cmnd = str;
    data.tokens_list = NULL;

    lexer(&data);
    // token_node = data.tokens_list;
    // while (token_node != NULL) 
	// {
    //     printf("Token: %s\n", token_node->value);
    //     token_node = token_node->next;
    // }
	
    // token_node = data.tokens_list;
    // while (token_node != NULL) {
    //     t_tokens *next_node = token_node->next;
    //     free(token_node->value);
    //     free(token_node);
    //     token_node = next_node;
    // }
    free(str);

    return 0;
}


// int main()
// {
// 	printf("%s\n", ft_substr("helloword", 1, 5));
// }