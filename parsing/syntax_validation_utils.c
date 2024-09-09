/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_validation_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykamboua <ykamboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 17:19:33 by ykamboua          #+#    #+#             */
/*   Updated: 2024/09/09 10:37:40 by ykamboua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	quotes_check(char *input)
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
		printf("%c\n",input[i]);
			// single_quoted = !single_quoted;
		if(input[i] == 34)
		printf("%c\n",input[i]);

			// double_quoted = !double_quoted;
		i++;
	}
	if(single_quoted == 1 || double_quoted == 1)
		return(1);
	return(0);
}
#include<stdio.h>
int main(int ac, char **av)
{
	char	*str;
	str = "echo \"He said 'hi'\"";
	// printf("%s\n",av[1]);
	printf("%d", inside_quotes(str));
}
