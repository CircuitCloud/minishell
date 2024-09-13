/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_validation_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykamboua <ykamboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 17:19:33 by ykamboua          #+#    #+#             */
/*   Updated: 2024/09/14 00:23:48 by ykamboua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int	is_valid_start_char(char *input, char c)
{
	int	i;
	i = 0;

	if(input[0] == c)
		return(1);
	return(0);
}

int	is_valid_end_char(char *input, char c)
{
	int	len;
	len = ft_strlen(input);

	if(input[len - 1] == c)
		return(1);
	return (0);
}

int	duplicate_operator(char *input, char c)
{
	int		i;
	char	*trimmed_input;

	i = 0;
	trimmed_input = ft_strtrim(input, " ");

	while (trimmed_input[i])
	{
		if(trimmed_input[i] == c)
		{
			i++;
			while (trimmed_input[i] == ' ')
				i++;
			if(trimmed_input[i] == c)
				return (1);
		}
		i++;
	}
	return (0);
}

int	open_quotes_check(char *input)
{
	int	i;
	int	single_quoted;
	int	double_quoted;

	single_quoted = 0;
	double_quoted = 0;
	i = 0;
	if(!input)
		return(1);
	while (input[i])
	{
		if (input[i] == 39)
			single_quoted = !single_quoted;
		if(input[i] == 34)
			double_quoted = !double_quoted;
		i++;
	}
	if(single_quoted == 1 || double_quoted == 1)
		return(1);
	return(0);
}


int	pipes_mispalced_check(char *input)
{
	int	i;
	i = 0;

	if(!input)
		return(1);
	if(input[i] == '|')
		return (1);
	while (input[i])
	{
		if(input[i] == '|')
		{
			i++;
			while (input[i] == ' ')
				i++;
			if (input[i] == '\0' || input[i] == '|')
				return (1);
		}
		i++;
	}
	return (0);
}

#include<stdio.h>
int main(int ac, char **av)
{
	(void) ac;
	char	*str;
	str = "    echo \"""""\"He said 'hi'\"";
	printf("%d", duplicate_operator(av[1], '|'));
}
