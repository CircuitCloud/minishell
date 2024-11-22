/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cahaik <cahaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 15:20:17 by cahaik            #+#    #+#             */
/*   Updated: 2024/11/21 01:25:01 by cahaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	execution(t_command *root, t_status *p)
{
	if (ft_strcmp(root->cmnd, "|") == 0)
		execute_pipe(root, &p);
	else
		execute_program(root, &p);
}
