SRCS =  ./src/main.c \
		./src/built-in/ft_cd.c \
		./src/built-in/ft_pwd.c \
		./src/parse/tokenizer.c \
		./src/parse/tokenizer_env.c \
		./src/parse/tokenizer_split.c \
		./src/error/error.c \
		./src/utils/ft_env.c \
		./src/utils/ft_strcmp.c \
		./src/exception/parse_exception.c

CC = gcc
LIBFT = libft
NAME = minishell

LIBS = $(LDFLAGS) $(CPPFLAGS) -lreadline

CFLAG = -Wall -Wextra -Werror
OBJS = $(SRCS:.c=.o)

all: make_libft $(NAME)

$(NAME): $(OBJS)
	$(CC) $(LIBFT)/libft.a $(CFLAG) $(LIBS) -I./ -o $(NAME) $(OBJS)

make_libft:
	make -C $(LIBFT)

.c.o :
	$(CC) $(LIBS) -I./ -c $< -o $@

clean:
	rm -f $(OBJS)
	make clean -C $(LIBFT)

fclean: clean
	rm -f $(NAME)
	make fclean -C libft

re: fclean all

.PHONY: all clean fclean re
