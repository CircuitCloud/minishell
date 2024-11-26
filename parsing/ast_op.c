/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykamboua <ykamboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 03:54:50 by ykamboua          #+#    #+#             */
/*   Updated: 2024/11/26 09:07:37 by ykamboua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_args_len(t_tokens *tokens)
{
	t_tokens	*word;
	int			file_delim_founded;
	int			args_len;

	file_delim_founded = 0;
	args_len = 0;
	word = tokens;
	while (word && word->type != PIPE)
	{
		if (word->type == I_RED || word->type == O_RED 
			|| word->type == APPEND || word->type == HERDOC)
			file_delim_founded++;
		if (word->type == WORD)
			args_len++;
		word = word->next;
	}
	args_len = args_len - file_delim_founded;
	return (args_len);
}

int	fill_args_array(t_tokens **current, t_command *single_command)
{
	int	i;

	i = 0;
	while (*current && (*current)->type == WORD)
	{
		if ((*current)->value && (*current)->empty_expand == 0)
		{
			if (!single_command->cmnd 
				|| ft_strcmp(single_command->cmnd, "") == 0)
			{
				if (ft_strcmp(single_command->cmnd, "") == 0)
					free(single_command->cmnd);
				single_command->cmnd = ft_strdup((*current)->value);
			}
			single_command->args[i] = ft_strdup((*current)->value);
			if (!single_command->args[i])
			{
				printf("faaailed to allocate memory for args[%d]\n", i);
			}
			i++;
		}
		(*current) = (*current)->next;
	}
	return (i);
}

void	cmd_(t_tokens **current, t_command **root, int arg_l, t_grp_ev_p *ev_p)
{
	t_command	*last_cmnd;
	t_command	*single_command;
	int			i;

	if ((*current) && (*current)->type == WORD && !(*current)->empty_expand)
		single_command = create_simple_command
			((*current)->value, arg_l, ev_p->ev);
	else
		single_command = create_simple_command(NULL, arg_l, ev_p->ev);
	i = fill_args_array(current, single_command);
	redir_(current, single_command, ev_p, &i);
	if (!*root)
		*root = single_command;
	else
		last_cmnd->right = single_command;
	last_cmnd = single_command;
}
