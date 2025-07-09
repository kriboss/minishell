NAME = minishell

CC = cc -Wall -Wextra -Werror

INCLUDES = -Iinclude -Ilibft

LIBFT = libft/libft.a

FILES = lexer/token.c lexer/main.c lexer/free.c lexer/process.c lexer/utils.c lexer/validate.c lexer/expand.c execution/execute.c execution/utils.c execution/export.c execution/unset.c execution/redirections.c execution/pipes.c execution/signals.c execution/ins_exp.c

OBJS = ${FILES:.c=.o}

%.o: %.c
	@${CC} ${INCLUDES} -c $< -o $@ > /dev/null

${NAME}: ${OBJS} | make_libft
	@${CC} ${OBJS} $(LIBFT) -lreadline -o ${NAME}
	@echo "minishell compiled"

make_libft:
	@make -s -C libft
	@echo "libft compiled"

all: ${NAME}

clean:
	@rm -f ${OBJS} ${BOBJS}
	@make -C libft clean > /dev/null
	@echo "object files got cleaned"

fclean: clean
	@rm -f ${NAME}
	@make -C libft fclean > /dev/null
	@echo "everything cleaned"

re: fclean all

.PHONY: all clean fclean re
