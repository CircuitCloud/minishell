/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykamboua <ykamboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:32:37 by ykamboua          #+#    #+#             */
/*   Updated: 2024/09/09 09:45:43 by ykamboua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
typedef	struct	s_argument
{
	char	*value;
	int		type;
}	t_argument;

typedef	struct s_redirection
{
	int				id; //to_disscuss
	int				type;
	char			*file;
	char			*delimiter;
	int				fd;
	struct s_redirection	*next_redir;
}	t_redirection;

typedef	struct	s_command
{
	char			*cmnd;
	t_argument		**args;
	t_redirection	*redir;
}	t_command;

typedef	struct	s_pipe
{
	t_command	*cmnd1;
	t_command	*cmnd2;
}	t_pipe;

#endif