CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = result.exe
OBJ = get_next_line.o get_next_line_utils.o

all: $(NAME)

$(NAME): $(OBJ)
	gcc $(CFLAGS) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re
