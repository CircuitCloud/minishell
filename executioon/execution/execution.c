/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cahaik <cahaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 15:20:17 by cahaik            #+#    #+#             */
/*   Updated: 2024/11/08 06:11:49 by cahaik           ###   ########.fr       */
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
// fach nsali should update type dyal ev f other files....
// exit_status = 0; in main