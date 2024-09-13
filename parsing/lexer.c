/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykamboua <ykamboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 19:39:34 by ykamboua          #+#    #+#             */
/*   Updated: 2024/09/13 21:43:42 by ykamboua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_token(char c)
{
	int	i;

	i = 0;
	while (c)
	{
		if(c == '|' || c == '\'' || c == '\"' || c == '>' || c == '<')
			return (1);
	}
	return (0);
}

// char	*extarct_from_quotes(char *input, int index)
// {
// 	int		i;
// 	int		start;
// 	int		end;
// 	char	*str;

// 	i = 0;
// 	start = -1;
// 	end = -1;
// 	while (input[i])
// 	{
// 		if(i == index)
// 		{
// 			start = i;
// 			break;
// 		}
// 		i++;
// 	}
// 	if(start == -1)
// 		return(NULL);
// 	i++;
// 	while (input[i])
// 	{
// 		if(input[i] == input[start])
// 		{
// 			end = i + 1;
// 			break;
// 		}
// 		i++;
// 	}
// 	if(end == -1)
// 		return(NULL);
// 	return (str = ft_substr(input, start, end - start), str);
// }

int	*extarct_from_quotes(char *input, int index)
{
	int		i;
	int		start;
	int		end;
	char	*str;

	i = 0;
	start = -1;
	end = -1;
	while (input[i])
	{
		if(i == index)
		{
			start = i;
			break;
		}
		i++;
	}
	if(start == -1)
		return(-1);
	i++;
	while (input[i])
	{
		if(input[i] == input[start])
		{
			end = i + 1;
			break;
		}
		i++;
	}
	return (end);
}

int	token_position_finder(char *input)
{
	int	i;
	int	pos;

	i = 0;
	while (input[i])
	{
		if(is_token(input[i]))
			pos = i;
		i++;
	}
}
int main()
{
	char *str;
	char *res;
	str = "'yh\"e\"l'loy | khjjk$l";
	res = extarct_from_quotes(str, 0);
	printf("%s\n", res);
}