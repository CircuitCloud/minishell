/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cahaik <cahaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 11:48:26 by cahaik            #+#    #+#             */
/*   Updated: 2024/11/27 00:39:33 by cahaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	pwd_(t_ev *ev, t_status *p)
{
	char	*str;

	str = getcwd(NULL, 0);
	(void)ev;
	if (str)
	{
		printf("%s\n", str);
		free(str);
	}
	p->exit_status = 0;
}
