/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykamboua <ykamboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 22:37:14 by ykamboua          #+#    #+#             */
/*   Updated: 2024/11/06 07:39:21 by ykamboua         ###   ########.fr       */
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
		if(c_1 == '<')
			return (HERDOC);
		return(I_RED);
	}
	else if (c == '>')
	{
		if(c_1 == '>')
			return (APPEND);
		return (O_RED);
	}
	return (0);
}
void	append_special_tokens_2(t_command *data, char *token, int type)
{
	t_tokens	*new_node;

	new_node = ft_lstneww(token, type);
	if(!new_node)
	{
		free(token);
		exit (1);
	}
	ft_lstadd_backk(&(data->tokens_list), new_node);
}
int append_special_tokens(t_command *data, char c, char c_1)
{
	int			type;
	int			res;
	char		*token;
		t_tokens	*new_node;

	res = 1;
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
	append_special_tokens_2(data, token, type);
	// new_node = ft_lstneww(token, type);
	// if(!new_node)
	// {
	// 	free(token);
	// 	exit (1);
	// }
	// ft_lstadd_backk(&(data->tokens_list), new_node);
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

	if(!input || start < 0 || start >= strlen(input))
		return(-1);
	// *type = WORD;
	while (input[i] && !is_whitespace(input[i]) && !is_token(input[i], input[i + 1])) 
	{
		if (input[i] == '\'' || input[i] == '\"')
		{
			// *type = WORD;
			i = quotes_handler(input, i, input[i]);
			if (i == -1) 
			{
				printf("Error: No closing quote found\n");
				exit(1);
			}
		}
		if(input[i] == ' ' || is_token(input[i], input[i + 1]))
			break;
		i++;
	}
	return (i);
}

void lexer(t_command	*data)
{
	int 		i;
	int			start;
	// int 		type;
	char 		*token;
	t_tokens	*new_token;

	i = 0;
	while (data->cmnd[i])
	{
		while (is_whitespace(data->cmnd[i]))
			i++;
		if(!is_token(data->cmnd[i], data->cmnd[i + 1]))
		{
			start = i;
			i = word_handler(data->cmnd, i);
			token = ft_substr(data->cmnd, start, i - start);
			if (token && ft_strlen(token))
			{
				new_token = ft_lstneww(token, WORD);
				ft_lstadd_backk(&(data->tokens_list), new_token);
			}
			free(token);
			// free(new_token);
		}
		if(is_token(data->cmnd[i], data->cmnd[i + 1]))
		{
			i+= append_special_tokens(data, data->cmnd[i], data->cmnd[i + 1]);
		}
	}
}

void print_ast(t_command *node, int level) 
{
    if (!node)
        return;
	
    for (int i = 0; i < level; i++)
        printf("  ");

    printf("Command: ---%s\n", node->cmnd);
    if (node->args) 
	{
		int i = 0;
        printf("arguments:----");
        while (node->args[i]) 
		{
            printf("(%s)", node->args[i]);
			i++;
        }
        printf("\n");
    }

    if (node->redir) 
	{
        printf("rdirections:-----\n");
		while (node->redir)
		{
			printf("file :    %s\n", node->redir->file);
			printf("delimiii :   %s\n", node->redir->delimiter);
			printf("%d\n", node->redir->type);
			node->redir= node->redir->next_redir;
		}
		
        // printf("%s\n", node->redir->file);
    }

    if (node->left)
	{
        printf("Llllleft:\n");
        print_ast(node->left, level + 1);
    }
    if (node->right) 
	{
        printf("Right:\n");
        print_ast(node->right, level + 1);
    }
}


// void print_ast(t_command *node, int level)
// {
//     if (!node) return;

//     for (int i = 0; i < level; i++) printf("  "); // Print indentation

//     if (node->type == PIPE)
//         printf("PIPE\n");
//     else
//         printf("COMMAND: %s\n", node->cmnd);

//     if (node->left)
//         print_ast(node->left, level + 1);
//     if (node->right)
//         print_ast(node->right, level + 1);
// }

int main()
{
	t_command 	data;
	t_command	*tree;
	t_command	*current_tree;
	
	t_tokens *token_node;
	char *str;

	str = readline("minii>");
	while (str)
	{
		data.cmnd = str;
		data.tokens_list = NULL;
		lexer(&data);
		token_node = data.tokens_list;
		expand_env(data.tokens_list);
		remove_quotes((data.tokens_list));
		tree = build_ast(data.tokens_list);
		// printf("%s\n",tree->cmnd);
		int i = 0;
		current_tree = tree;
		// while (current_tree->args[i])
		// {
		// 	printf("%s\n", current_tree->args[i]);
		// 	i++;
		// }
		// printf("hna\n");

		print_ast(tree, 0);
		// while (tree)
		// {
		// 	if(tree->left)
		// 		printf("left : %s\n", tree->left->cmnd);
		// 	if(tree->right)
		// 		printf("right : %s\n", tree->right->cmnd);
		// 	tree = tree->left;
		// }
		// while (token_node) 
		// {
		// 	printf("Token : (%s)\n", token_node->value);
		// 	// printf("type : (%d)\n", token_node->type);
		// 	// printf("Token : (%d)\n", token_node->type);
		// 	token_node = token_node->next;
		// }
		free(str);  
		str = readline("minii>");
	}
	return 0;
}
