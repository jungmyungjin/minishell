SRCS =  ./src/main.c

CC = gcc
LIBFT = libft
NAME = minishell

LIBS = ${LDFLAGS} ${CPPFLAGS} -lreadline

CFLAG = -Wall -Wextra -Werror
OBJS = $(SRCS:.c=.o)

MINISHELL_LIB = minishell.a

$(NAME): $(OBJS)
	make -C $(LIBFT)
	ar rcs $(MINISHELL_LIB) $(OBJS)
	$(CC)  $(CFLAG) $(MINISHELL_LIB) $(LIBFT)/libft.a $(LIBS) -o $(NAME)
	#$(CC) $(CFLAG) $(OBJS) -o $(NAME)

all: $(NAME)


clean:
	rm -f $(OBJS)
	make clean -C $(LIBFT)

fclean: clean
	rm -f $(NAME)
	make fclean -C libft

re: fclean all

.PHONY: all clean fclean re
