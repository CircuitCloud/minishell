CC = gcc
# CFLAGS = -Wall -Wextra -Werror
LIBFT = ../libft/libft.a
# OBJ = syntax_validation_utils.o
EXECUTABLE = main

SRC =  lexer2.c list.c

OBJ = $(SRC:.c=.o)

# LIBFT :
# 	make -C ../libft

all : $(EXECUTABLE)

$(EXECUTABLE) : $(OBJ)
	make -C ../libft
	$(CC)  -o $(EXECUTABLE) -lreadline  $(OBJ) $(LIBFT)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	make -C ../libft clean
	rm -f $(OBJ)
fclean : clean
	make -C ../libft fclean
	rm -f $(EXECUTABLE)
re : fclean all 

.PHONY: all clean fclean re