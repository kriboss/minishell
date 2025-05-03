# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kbossio <kbossio@student.42firenze.it>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/20 12:08:15 by kbossio           #+#    #+#              #
#    Updated: 2025/01/29 20:48:00 by kbossio          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

COMPILER = gcc

FLAGS = -Wall -Werror -Wextra

FILES = ft_printf/ft_printf.c ft_printf/ft_printf_utils.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c get_next_line/get_next_line_bonus.c get_next_line/get_next_line_utils_bonus.c ft_atoi.c ft_isprint.c ft_putchar_fd.c ft_striteri.c ft_strnstr.c ft_bzero.c ft_itoa.c ft_putendl_fd.c ft_strjoin.c ft_strrchr.c ft_calloc.c ft_memchr.c ft_putnbr_fd.c ft_strlcat.c ft_strtrim.c ft_isalnum.c ft_memcmp.c ft_putstr_fd.c ft_strlcpy.c ft_substr.c ft_isalpha.c ft_memcpy.c ft_split.c ft_strlen.c ft_tolower.c ft_isascii.c ft_memmove.c ft_strchr.c ft_strmapi.c ft_toupper.c ft_isdigit.c ft_memset.c ft_strdup.c ft_strncmp.c

OBJS = ${FILES:.c=.o}

BFILES = ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c

BOBJS = ${BFILES:.c=.o}


${NAME}: ${OBJS}
	ar -rcs ${NAME} ${OBJS}

%.o: %.c
	${COMPILER} ${FLAGS} -c $< -o $@

all: ${NAME}

clean:
	rm -f ${OBJS} ${BOBJS}

fclean: clean
	rm -f ${NAME}

re: fclean all

bonus: $(OBJS) $(BOBJS)
	ar -rcs $(NAME) $(OBJS) $(BOBJS)

.PHONY: all clean fclean re bonus
