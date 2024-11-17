/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykamboua <ykamboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 22:37:14 by ykamboua          #+#    #+#             */
/*   Updated: 2024/11/17 22:40:17 by ykamboua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int is_token(char c, char c_1) 
{
	if ((c == '<' && c_1 == '<') || (c == '>' && c == '>'))
		return (1);
	else if(c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

int define_type(char c, char c_1)
{
	if (c == '|')
		return(PIPE);
	else if (c == '<')
	{
		if(c_1 && c_1 == '<')
			return (HERDOC);
		return(I_RED);
	}
	else if (c == '>')
	{
		if(c_1 && c_1 == '>')
			return (APPEND);
		return (O_RED);
	}
	return (0);
}

void	append_special_tokens_2(t_tokens *tokens, char *token, int type)
{
	t_tokens	*new_node;

	new_node = ft_lstneww(token, type);
	if(!new_node)
	{
		free(token);
		exit (1);
	}
	ft_lstadd_backk(&(tokens), new_node);
}

int append_special_tokens(t_tokens *tokens, char c, char c_1)
{
	int			type;
	int			res;
	char		*token;

	res = 1;
	token = NULL; // zidta ana chaima 3la wed l flags
	type = define_type(c, c_1);
	if (type == PIPE)
		token = ft_strdup("|");
	else if (type == I_RED)
		token = ft_strdup("<");
	else if (type == O_RED)
		token = ft_strdup(">");
	else if (type == HERDOC)
	{
		token = ft_strdup("<<");
		res = 2;
	}
	else if (type == APPEND)
	{
		token = ft_strdup(">>");
		res = 2;
	}
	if(!token)
		exit (1);
	append_special_tokens_2(tokens, token, type);
	return (res);
}

int is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

int quotes_handler(char *input, int start, char quote_char)
{
	int	i;

	i = start + 1;
	if(!input || start >= ft_strlen(input) || start < 0)
		return (-1);
	while (input[i])
	{
		if (input[i] == quote_char)
			return (i);
		i++;
	}
	return (-1);
}

int word_handler(char *input, int start)
{
	int i;

	i = start;

	if(!input || start < 0 || start >= ft_strlen(input))
		// exit(1);
		return(0);
	while (input[i] && !is_whitespace(input[i]) && !is_token(input[i], input[i + 1])) 
	{
		if (input[i] == '\'' || input[i] == '\"')
		{
			i = quotes_handler(input, i, input[i]);
			if (i == -1) 
			{
				printf("Error: no closing quote found\n");
				return(-1);
			}
		}
		if(input[i] == ' ' || is_token(input[i], input[i + 1]))
			break;
		i++;
	}
	return (i);
}

int lexer(t_tokens	*tokens, char *str)
{
	int 		i;
	int			start;
	char 		*token;
	t_tokens	*new_token;

	i = 0;
	if(!tokens || !str)
		// exit(1);
		return(1);
	while (str[i])
	{
		while (is_whitespace(str[i]))
			i++;
		if(!is_token(str[i], str[i + 1]))
		{
			start = i;
			i = word_handler(str, i);
			if(i == -1)
				return(-1);
			token = ft_substr(str, start, i - start);
			// if(!token)
			//----free
				// exit(1);
			if(token && ft_strlen(token))
			{
				new_token = ft_lstneww(token, WORD);
				// if(!new_token)
				// 	exit(1);
				ft_lstadd_backk(&(tokens), new_token);
			}
			free(token);
			// free(new_token);
		}
		if(is_token(str[i], str[i + 1]))
		{
			i+= append_special_tokens(tokens, str[i], str[i + 1]);
		}
	}
	return(0);
}

void print_ast(t_command *node, int level) 
{
    if (!node)
        return;
	
    printf("------- Command: ---------\n\n\n");
	// if(node->cmnd)
	printf("  %s\n", node->cmnd);
    if (node->args) 
	{
		int i = 0;
        printf("arguments : ");
        while (node->args[i]) 
		{
            printf("(%s)", node->args[i]);
			i++;
        }
        printf("\n");
    }

    if (node->redir) 
	{
        printf("rdirections : \n");
		while (node->redir)
		{
			printf("	file :    %s\n", node->redir->file);
			printf("	delimiii :   %s\n", node->redir->delimiter);
			// printf("	%d\n", node->redir->type);
			node->redir= node->redir->next_redir;
		}
        // printf("%s\n", node->redir->file);
    }
    if (node->left)
	{
        printf("----------Llllleft:\n");
        print_ast(node->left, level + 1);
    }
    if (node->right) 
	{
        printf("----------Right:\n");
        print_ast(node->right, level + 1);
    }
}
