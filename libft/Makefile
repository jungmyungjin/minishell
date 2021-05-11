# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ychoi <ychoi@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/29 15:24:48 by ychoi             #+#    #+#              #
#    Updated: 2021/01/09 01:28:28 by ychoi            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_DIR = ./
SRCS_BONUS_DIR = ./

AR = ar
CC = gcc

ARFLAGS = rc
CFLAGS = -c -Wall -Wextra -Werror

SRCS = $(SRC_DIR)ft_strlen.c \
		$(SRC_DIR)ft_strlcat.c \
		$(SRC_DIR)ft_isalpha.c \
		$(SRC_DIR)ft_isdigit.c \
		$(SRC_DIR)ft_toupper.c \
		$(SRC_DIR)ft_tolower.c \
		$(SRC_DIR)ft_isascii.c \
		$(SRC_DIR)ft_isprint.c \
		$(SRC_DIR)ft_isalnum.c \
		$(SRC_DIR)ft_strncmp.c \
		$(SRC_DIR)ft_memset.c \
		$(SRC_DIR)ft_bzero.c \
		$(SRC_DIR)ft_memcpy.c \
		$(SRC_DIR)ft_memccpy.c \
		$(SRC_DIR)ft_memmove.c \
		$(SRC_DIR)ft_memchr.c \
		$(SRC_DIR)ft_memcmp.c \
		$(SRC_DIR)ft_calloc.c \
		$(SRC_DIR)ft_strchr.c \
		$(SRC_DIR)ft_strrchr.c \
		$(SRC_DIR)ft_strlcpy.c \
		$(SRC_DIR)ft_atoi.c \
		$(SRC_DIR)ft_strdup.c \
		$(SRC_DIR)ft_strnstr.c \
		$(SRC_DIR)ft_putchar_fd.c \
		$(SRC_DIR)ft_putstr_fd.c \
		$(SRC_DIR)ft_putendl_fd.c \
		$(SRC_DIR)ft_putnbr_fd.c \
		$(SRC_DIR)ft_substr.c \
		$(SRC_DIR)ft_strjoin.c \
		$(SRC_DIR)ft_strtrim.c \
		$(SRC_DIR)ft_itoa.c \
		$(SRC_DIR)ft_strmapi.c \
		$(SRC_DIR)ft_split.c

SRCS_BONUS = $(SRC_DIR)ft_lstnew.c \
				$(SRC_DIR)ft_lstadd_front.c \
				$(SRC_DIR)ft_lstsize.c \
				$(SRC_DIR)ft_lstlast.c \
				$(SRC_DIR)ft_lstadd_back.c \
				$(SRC_DIR)ft_lstdelone.c \
				$(SRC_DIR)ft_lstclear.c \
				$(SRC_DIR)ft_lstiter.c \
				$(SRC_DIR)ft_lstmap.c



NAME = libft.a
HEADERS = libft.h

OBJS = $(SRCS:.c=.o)
BONS_OBJS = ${SRCS_BONUS:.c=.o}

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(SRCS) $(HEADERS)
	$(AR) $(ARFLAGS) $(NAME) $(OBJS)


all: $(NAME)

bonus: $(OBJS) $(BONS_OBJS)
	$(CC) $(CFLAGS) $(SRCS) $(HEADERS)
	$(AR) $(ARFLAGS) $(NAME) ${OBJS} $(BONS_OBJS)

clean:
	rm -rf $(OBJS) $(BONS_OBJS)

fclean:	clean
	rm -rf $(NAME)

re: fclean all

.PHONY:	all clean fclean re bonus
