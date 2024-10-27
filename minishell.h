/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykamboua <ykamboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:32:37 by ykamboua          #+#    #+#             */
/*   Updated: 2024/10/26 23:13:57 by ykamboua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
// #include "parsing/list.c"
#include "libft/libft.h"
#include <readline/readline.h>

# define PIPE 1
# define I_RED 2
# define O_RED 3
# define HERDOC 4
# define APPEND 5
# define WORD 6
# define QUOTED 7

typedef	struct	s_argument
{
	char	*value;
	int		type;
}	t_argument;



typedef	struct	s_tokens
{
	char	*value;
	int		type;
	struct	s_tokens	*next;
}	t_tokens;


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
	char 			**ev; // environement variable (main(int ac, char **av, char **ev) for execve and path)
	char		**args; // changing "t_argument to char "
	t_tokens		*tokens_list; // changing "t_argument to char "
	t_redirection	*redir;
	struct s_command		*left; // left child of tree
	struct s_command		*right; // right child of tree
}   t_command;

typedef	struct	s_pipe
{
	t_command	*cmnd1;
	t_command	*cmnd2;
}	t_pipe;

t_tokens	*ft_lstneww(char *cmnd, int type);
t_tokens	*ft_lstlastt(t_tokens *lst);
void		ft_lstadd_backk(t_tokens **lst, t_tokens *new);
int is_token(char c, char c_1);
int	open_quotes_check(char *input);
int quotes_handler(char *input, int start, char quote_char);
char	*quotes_eliminator(char *token);
void	quotes(t_tokens *tokens);
//expansion_________________________________________________________________________
char	*get_env_token(char *token);
void	expand_env(t_tokens *tokens);
int is_whitespace(char c);

//quuotes
// void	remove_quotes_from_tokens(t_tokens *tokens);
void	remove_quotes(t_tokens *tokens);
#endif