/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cahaik <cahaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 14:57:53 by cahaik            #+#    #+#             */
/*   Updated: 2024/09/14 16:00:33 by cahaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_EXECUTION_H
# define MINISHELL_EXECUTION_H

#ifndef INPUT_RED
# define INPUT_RED 1
#endif 

#ifndef OUTPUT_RED
# define OUTPUT_RED 2
#endif 

#ifndef APPEND_RED
# define APPEND_RED 3
#endif 

#ifndef HERE_DOC
# define HERE_DOC 4
#endif

#ifndef TYPE_PIPE
# define TYPE_PIPE 5
#endif

#ifndef  TYPE_REDIRECT
# define TYPE_REDIRECT 6
#endif


#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include "libft/libft.h"

typedef	struct	s_argument
{
	char	*value;
	int		type;
}	t_argument;

typedef	struct s_redirection
{
	int				id; //to_disscuss
	int				type;//| > | >> | << | < 
	char			*file;
	char			*delimiter;
	int				fd;
	struct s_redirection	*next_redir;
}	t_redirection;

typedef	struct	s_command
{
	int				type;
	char			*cmnd;
	char 			**ev; // environement variable (main(int ac, char **av, char **ev) for execve and path)
	char		**args; // changing "t_argument to char "
	t_redirection	*redir;
	struct s_command		*left; // left child of tree
	struct s_command		*right; // right child of tree
}   t_command;

typedef	struct	s_pipe
{
	t_command	*cmnd1;
	t_command	*cmnd2;
}	t_pipe;

int search(char **cmd, char **ev);
int	ft_strncmp(const char *dest, const char *src, size_t n);
size_t	ft_strlen(const char *str);
int	ft_strcmp(char *dest, char *src);
int search_bin(char **cmd, char *ev, char **env);
void execute_program(t_command *root);
int execute_pipe(t_command *root);
void out_redirect(t_command *root);
void input_redirect(t_command *root);
void redirection(t_command *root);
void execution(t_command *root);
t_command *create_right_child(char **env); // for testing 
t_command *create_right(char **env); // for testing
t_command *create_left(char **env); // for testing
t_command *create_tree(char **env); // for testing

#endif 