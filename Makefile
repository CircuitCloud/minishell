CC = gcc
# CFLAGS = -Wall -Wextra -Werror  #-g -fsanitize=address 
LIBFT = libft/libft.a

EXECUTABLE = minishell

SRC =   parsing/syntax_validation_utils.c parsing/syntax_validation.c \
		parsing/quotes_handler.c parsing/expansion.c \
		parsing/list.c parsing/ast_op.c parsing/build_ast.c \
		executioon/builtins/cd.c executioon/builtins/echo.c executioon/builtins/env.c \
		executioon/builtins/exit.c executioon/builtins/export.c executioon/builtins/export_util.c \
		executioon/builtins/pwd.c executioon/builtins/unset.c executioon/env/env_linked.c \
		executioon/execution/exec.c executioon/execution/exec_util.c executioon/execution/execution.c \
		executioon/execution/pipes.c \
		executioon/execution/redirection.c executioon/signals/signal.c executioon/ft_strcmp.c\
		executioon/execution/heredoc.c executioon/execution/redirections_utils.c \
		executioon/print_error.c main.c parsing/lexer_utils.c parsing/lexer2.c parsing/env_list.c\
		free.c\

OBJ = $(SRC:.c=.o)

all : $(EXECUTABLE)

$(EXECUTABLE) : $(OBJ)
	make -C libft
	$(CC) -o $(EXECUTABLE) -lreadline  $(OBJ) $(LIBFT) -L$(HOME)/readline/lib
%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I$(HOME)/readline/include

# $(EXECUTABLE) : $(OBJ)
# 	make -C libft
# 	$(CC) -o $(EXECUTABLE) -lreadline  $(OBJ) $(LIBFT) -L/goinfre/cahaik/homebrew/opt/readline/lib  #-g -fsanitize=address
# %.o : %.c
# 	$(CC) $(CFLAGS) -c $< -o $@ -I/goinfre/cahaik/homebrew/opt/readline/include #-g -fsanitize=address

clean :
	make -C libft clean
	rm -f $(OBJ)
fclean : clean
	make -C libft fclean
	rm -f $(EXECUTABLE)
re : fclean all 

.PHONY: all clean fclean re