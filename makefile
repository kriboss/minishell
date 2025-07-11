NAME = minishell

CC = cc -Wall -Wextra -Werror -g

INCLUDES = -Iinclude -Ilibft

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

FILES = lexer/helper.c lexer/hd_utils.c lexer/heredoc.c lexer/quotes.c lexer/tokens.c lexer/token.c \
		lexer/main.c lexer/free.c lexer/process.c lexer/utils.c lexer/validate.c lexer/expand.c \
		lexer/update_status_code.c lexer/is_special_special.c \
		execution/execute.c execution/utils.c execution/export.c execution/unset.c execution/redirections.c \
		execution/pipes.c execution/exit.c execution/buildin.c execution/env_order.c execution/signals.c \
		execution/ins_exp.c execution/exec_ext.c \

OBJS = ${FILES:.c=.o}

%.o: %.c
	@${CC} ${INCLUDES} -c $< -o $@ > /dev/null

${NAME}: ${OBJS} ${LIBFT}
	@${CC} ${OBJS} $(LIBFT) -lreadline -o ${NAME}
	@echo "minishell compiled"

${LIBFT}:
	@make -s -C $(LIBFT_DIR)
	@echo "libft compiled"

all: ${NAME}

clean:
	@rm -f ${OBJS}
	@make -C $(LIBFT_DIR) clean > /dev/null
	@echo "object files got cleaned"

fclean: clean
	@rm -f ${NAME}
	@make -C $(LIBFT_DIR) fclean > /dev/null
	@echo "everything cleaned"

re: fclean all

.PHONY: all clean fclean re

