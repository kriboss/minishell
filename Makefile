NAME = minishell

CC = cc -Wall -Wextra -Werror

INCLUDES = -Iinclude -Ilibft

LIBFT = libft/libft.a

FILES = execution/start.c execution/execute.c execution/utils.c execution/export.c execution/unset.c execution/redirections.c execution/pipes.c execution/signals.c

OBJS = ${FILES:.c=.o}

%.o: %.c
	${CC} ${INCLUDES} -c $< -o $@

${NAME}: ${OBJS} | make_libft
	${CC} ${OBJS} $(LIBFT) -lreadline -o ${NAME}

make_libft:
	@make -s -C libft
	@echo "libft compiled"

all: ${NAME}

clean:
	rm -f ${OBJS} ${BOBJS}
	make -C libft clean

fclean: clean
	rm -f ${NAME}
	make -C libft fclean

re: fclean all

.PHONY: all clean fclean re
