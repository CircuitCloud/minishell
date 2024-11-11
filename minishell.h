/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cahaik <cahaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:32:37 by ykamboua          #+#    #+#             */
/*   Updated: 2024/11/11 03:57:58 by cahaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <signal.h>
// #include "parsing/list.c"
# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

# define PIPE 1
# define I_RED 2
# define O_RED 3
# define HERDOC 4
# define APPEND 5
# define WORD 6
# define QUOTED 7

typedef struct s_status
{
	int exit_status;
	int check_redir;
	int newfd_in;
	int newfd_out;
	int last_herdoc;
	int for_redir_check;
}	t_status;

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

typedef struct s_ev
{
	char		*line;
	char		*name;
	char		*value;
	struct s_ev	*next;
	struct s_ev	*previous;
}	t_ev;

typedef	struct	s_command
{
	char				*cmnd;
	t_ev				*ev;
	char				**args;
	t_tokens			*tokens_list;
	t_redirection		*redir;
	struct s_command	*left;
	struct s_command	*right;
}   t_command;

typedef	struct	s_hdoc_inputs
{
	char					*value;
	struct s_hdoc_inputs	*next;
} t_hdoc_inputs;

typedef	struct	s_pipe
{
	t_command	*cmnd1;
	t_command	*cmnd2;
}	t_pipe;

extern int gqq_signal;

t_tokens	*ft_lstneww(char *cmnd, int type);
t_tokens	*ft_lstlastt(t_tokens *lst);
void		ft_lstadd_backk(t_tokens **lst, t_tokens *new);
int is_token(char c, char c_1);
int	open_quotes_check(char *input);
int quotes_handler(char *input, int start, char quote_char);
char	*quotes_eliminator(char *token);
void	quotes(t_tokens *tokens);
//expansion_________________________________________________________________________
char    *get_env_token(char *token, t_ev *ev);
void	expand_env(t_tokens *tokens, t_ev *ev);
int is_whitespace(char c);

//quuotes
// void	remove_quotes_from_tokens(t_tokens *tokens);
void	remove_quotes(t_tokens *tokens);

//hdooc
t_hdoc_inputs	*hdoc_parser(t_tokens *tokens);
t_command	*build_ast(t_tokens *tokens, t_ev *ev, t_status *p);
void lexer(t_command    *data);
char	*search_ev_value(char *exp_name, t_ev *env);

//--------------------added by execution------------------------------//
int				valide_var(char *arg);
int				ft_strcmp(char *dest, char *src);
int				create_struct(char *env, t_ev **ev);
int				search(char **cmd, t_ev *ev, t_status **p);
int				redirect_check(t_command *root, t_status **p);
int				search_bin(char **cmd, char *p, t_status **p_);
int				_spaces(char *str, int *sign, int *i, int func);
int				in_redir(t_redirection *root_redir, t_status **p);
int				out_redir(t_redirection *root_redir, t_status **p);
int				append_redir(t_redirection *root_redir, t_status **p);
int				ft_strncmp(const char *dest, const char *src, size_t n);
void			signals(int c);
void			pwd_(t_ev *ev);
void			env_(t_ev *ev, t_status **p);
void			exit_(char **arg, t_status **p);
void			echo_(char **arg, t_status **p);
void			unset_helper(t_ev **ev, char *name);
void			execution(t_command *root,t_status *p);
void			cd_(t_ev **ev, char *arg, t_status **p);
void			ft_lstadd_back_env(t_ev **lst, t_ev *new);
void			redirection(t_command *root, t_status **p);
void			execute_pipe(t_command *root, t_status **p);
void			unset_(t_ev **ev, char **name, t_status **p);
void			value_helper(char **value, char *arg, char c);
void			export_(char **args, t_ev **ev, t_status **p);
void			execute_program(t_command *root, t_status **p);
void			exit_many_args(t_status **p, int err, char *arg);
void			last_heredocc(t_redirection *heredoc, char *name);
void			out_redirect(t_redirection *root_redir, t_status* *p);
void			input_redirect(t_redirection *root_redir, t_status **p);
void			print_error(char *err, int type, t_status **p_, int exit_s);
t_ev			*environ(char **env);
t_ev			*ft_lstlast_env(t_ev *lst);
long long		atoi_exit(char *str, int *err);
t_ev			*ft_lst_new_env(char *line, char *name, char *value);
void			heredocc(t_redirection *heredoc, t_status **p);

void			print_ast(t_command *node, int level);
void			all_heredocs(t_redirection *heredoc, t_status **p);
int				last_herdoc_number(t_command copy, int option);
int				status_exec_program(int status);

#endif