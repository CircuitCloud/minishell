/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cahaik <cahaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:32:37 by ykamboua          #+#    #+#             */
/*   Updated: 2024/11/27 04:44:37 by cahaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

# define PIPE 1
# define I_RED 2
# define O_RED 3
# define HERDOC 4
# define APPEND 5
# define WORD 6

typedef struct s_expand_data
{
	char	*token;
	char	*str;
	int		double_quoted;
	int		single_quoted;
	int		i;
	int		start;
}	t_expand_data;

typedef struct s_redir_data
{
	char	*file;
	char	*delimiter;
	char	*raw_delimiter;
	int		type;
	int		hdoc_expand;
}	t_redir_data;

typedef struct s_status
{
	int		exit_status;
	int		check_redir;
	int		newfd_in;
	int		newfd_out;
	int		last_herdoc;
	int		for_redir_check;
	char	**env;
}	t_status;

typedef struct s_argument
{
	char	*value;
	int		type;
}	t_argument;

typedef struct s_tokens
{
	char			*value;
	int				type;
	int				hdoc_expand;
	int				empty_expand;
	char			*raw_delimiter;
	struct s_tokens	*next;
}	t_tokens;

typedef struct s_redirection
{
	int						type;
	char					*file;
	char					*delimiter;
	int						hdoc_need_expand;
	char					*delimiter_be4expand;
	int						fd;
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

typedef struct s_command
{
	char				*cmnd;
	int					type;
	t_ev				*ev;
	char				**args;
	t_tokens			*tokens_list;
	t_redirection		*redir;
	struct s_command	*left;
	struct s_command	*right;
}	t_command;

typedef struct s_hdoc_inputs
{
	char					*value;
	struct s_hdoc_inputs	*next;
}	t_hdoc_inputs;

typedef struct s_pipe
{
	t_command	*cmnd1;
	t_command	*cmnd2;
}	t_pipe;

typedef struct s_grp_ev_p
{
	t_ev		*ev;
	t_status	*p;
	char		*str;
}	t_grp_ev_p;

t_command		*init_pipe_cmnd(t_ev *ev);
t_command		*build_ast(t_tokens *tokens, t_ev *ev, t_status *p);
t_command		*create_simple_command(char *cmnd, int args_index, t_ev *ev);
t_redirection	*new_redir(t_redir_data *data_redir, t_ev *ev, t_status *p);
t_tokens		*ft_lstneww(char *cmnd, int type);
t_tokens		*ft_lstlastt(t_tokens *lst);
void			free_tree(t_command *root);
void			add_redir_cmnd(t_command *command, t_redirection *redir);
void			ft_lstadd_backk(t_tokens **lst, t_tokens *new);
int				is_token(char c, char c_1);
int				quotes_handler(char *input, int start, char quote_char);
char			*quotes_eliminator(char *token);
int				is_whitespace(char c);
int				lexer(t_command	*data);
char			*get_env_token(char *token, t_ev *ev, t_status *p);
void			expand_env(t_tokens *tokens, t_ev *ev, t_status *p);
char			*search_ev_value(char *exp_name, t_ev *env);
void			remove_quotes(t_tokens *tokens);
int				valid_next(t_tokens *tokens, char *c);
int				is_valid_start(t_tokens *tokens, int d);
int				is_valid_end(t_tokens *tokens);
int				duplicate_operator(t_tokens *tokens, int type);
int				syntaxe_validation(t_tokens *token, t_status *ex_status);
void			free_tokens_list(t_tokens *tokens);
char			*hdoc_expand(char *token, t_ev *ev, t_status *p);
char			*extract_var(char *str, int *pos);
char			*safe_ft_strjoin(char *s1, char *s2, int flag);
int				count_args_len(t_tokens *tokens);
int				fill_args_array(t_tokens **current, t_command *single_command);
void			redir_2(t_tokens **current, 
					t_command *cmd, t_ev *ev, t_status *p);
void			redir_(t_tokens **current, 
					t_command *cmd, t_grp_ev_p *ev_p, int *i);
void			pipe_(t_tokens **current, t_ev *ev, 
					t_command **root, t_status *p);
void			cmd_(t_tokens **current, 
					t_command **root, int arg_l, t_grp_ev_p *ev_p);
void			expand_single_quotes(t_expand_data *expand_data);
void			expand_double_quotes(t_expand_data *expand_data, 
					t_ev *ev, t_status *p);
void			expd_no_quoted_word(t_expand_data *exp, t_ev *ev, t_status *p);
char			*extract_var(char *str, int *pos);
void			free_token(char **token);
int				define_type(char c, char c_1);
int				word_handler(char *input, int start);

char			*ft_strtrim_execution(char const *s1, char const *set);
int				valide_var(char *arg);
int				ft_strcmp(char *dest, char *src);
int				create_struct(char *env, t_ev **ev);
int				search(char **cmd, t_ev *ev, t_status *p);
int				redirect_check(t_command *root, t_status *p);
int				search_bin(char **cmd, char *p, t_status *p_);
int				_spaces(char *str, int *sign, int *i, int func);
int				in_redir(t_command *root, 
					t_redirection *root_redir, t_status *p, int cmd);
int				out_redir(t_command *root, 
					t_redirection *root_rdir, t_status *p, int cmd);
int				append_redir(t_command *root, 
					t_redirection *redir, t_status *p, int cmd);
int				ft_strncmp(const char *dest, const char *src, size_t n);
void			free_redirect(t_redirection *redir);
void			signals(int c);
void			pwd_(t_ev *ev, t_status *p);
void			sig_handler_child(int sig);
void			sig_handler(int sig);
void			env_(t_ev *ev, t_status *p);
void			exit_(t_command *root, char **arg, t_status *p);
void			echo_(char **arg, t_status *p);
void			perror_(char *err, t_status *p);
void			unset_helper(t_ev **ev, char *name);
void			cd_(t_ev **ev, char *arg, t_status *p);
void			ft_lstadd_back_env(t_ev **lst, t_ev *new);
void			redirection(t_command *root, t_status *p);
void			execute_pipe(t_command *root, t_status *p);
void			unset_(t_ev **ev, char **name, t_status *p);
void			value_helper(char **value, char *arg, char c);
void			export_(char **args, t_ev **ev, t_status *p);
int				execute_program(t_command *root, t_status *p);
void			exit_many_args(t_command *root, 
					t_status *p, int err, char *arg);
void			last_heredocc(t_command *rt, 
					t_redirection *hdc, t_status *p, int cmd);
void			out_redirect(t_command *root, 
					t_redirection *root_redir, t_status *p);
void			input_redirect(t_command *root, 
					t_redirection *root_redir, t_status *p);
void			print_error(char *err, int type, t_status *p_, int exit_s);
t_ev			*environ(char **env);
t_ev			*ft_lstlast_env(t_ev *lst);
long long		atoi_exit(char *str, int *err);
t_ev			*ft_lst_new_env(char *line, char *name, char *value);
void			heredocc(t_redirection *heredoc, 
					t_ev *ev, t_status *p);
void			all_heredocs(t_redirection *heredoc, t_ev *ev, t_status *p);
int				last_herdoc_number(t_command copy);
int				status_exec_program(int status, int c);
void			dup_failed(t_command *root, t_status *p, int c);
void			free_env(t_ev *ev);
void			ft_free(t_command *root, t_status *p, int i);
void			lot_of_args(t_command *root, char **arg, t_status *p);
int				exit_helper(char *arg, int *err);
void			free_splited(char **str);
char			**store_env(t_command *root, t_ev *ev, t_status *p);
void			fork_failed(t_status *p);
void			original_fd(t_command *root, t_status *p);
int				if_builtin(t_command *root, t_status *p);

void			print_ast(t_command *node, int level);//todelte
#endif