/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cahaik <cahaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 14:57:53 by cahaik            #+#    #+#             */
/*   Updated: 2024/09/09 10:26:10 by cahaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_EXECUTION_H
# define MINISHELL_EXECUTION_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "libft/libft.h"

int search(char *cmd, char **ev);
int	ft_strncmp(const char *dest, const char *src, size_t n);
size_t	ft_strlen(const char *str);
int	ft_strcmp(char *dest, char *src);
int search_bin(char *cmd, char *ev, char **env);



#endif 