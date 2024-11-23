/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_util1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cahaik <cahaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 07:52:06 by cahaik            #+#    #+#             */
/*   Updated: 2024/11/23 08:26:14 by cahaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	redirect_check(t_command *root, t_status **p)
{
	(*p)->newfd_out = dup(1);
	(*p)->newfd_in = dup(0);
	redirection(root, p);
	if ((*p)->check_redir == 1)
		return (1);
	return (0);
}

int	if_builtin(t_command *root, t_status **p)
{
	if (ft_strcmp(root->cmnd, "echo") == 0)
		echo_(root->args + 1, p);
	else if (ft_strcmp(root->cmnd, "cd") == 0)
		cd_(&(root->ev), root->args[1], p);
	else if (ft_strcmp(root->cmnd, "env") == 0)
		env_(root->ev, p);
	else if (ft_strcmp(root->cmnd, "export") == 0)
		export_(root->args + 1, &(root->ev), p);
	else if (ft_strcmp(root->cmnd, "pwd") == 0)
		pwd_(root->ev, p);
	else if (ft_strcmp(root->cmnd, "unset") == 0)
		unset_(&(root->ev), (root->args + 1), p);
	else if (ft_strcmp(root->cmnd, "exit") == 0)
		exit_(root, root->args + 1, p);
	else
		return (1);
	return (0);
}

void	malloc_failed(t_command *root, t_status *p)
{
	write(2, "minishell : failed to allocate\n", 31);
	ft_free(root, p, 0);
	p->exit_status = 1;
	exit (p->exit_status);
}

char	**store_env(t_command *root, t_ev *ev, t_status *p)
{
	int		n;
	t_ev	*enm;
	char	**env;

	n = 0;
	enm = ev;
	while (ev)
	{
		n++;
		ev = ev->next;
	}
	env = malloc(sizeof(char *) * (n + 1));
	if (!env)
		malloc_failed(root, p);
	ev = enm;
	n = 0;
	while (ev && ev->line)
	{
		env[n] = ft_strdup(ev->line);
		n++;
		ev = ev->next;
	}
	env[n] = NULL;
	return (env);
}
