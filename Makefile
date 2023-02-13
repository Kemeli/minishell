SRC =		main.c \


LIBFT =		libft/libft.a

NAME =		minishell
FLAGS =		-Wall -Wextra -Werror

OBJS = ${SRC:%.c=%.o} 

all: ${NAME}

${NAME}: ${LIBFT} ${OBJS}
	cc -g -lreadline ${FLAGS} ${OBJS} ${LIBFT} -o $@

%.o: %.c
	cc -g -c ${FLAGS} $< -o $@

${LIBFT}:
	make -sC libft/

clean: 
	rm -f ${OBJS}
	make clean -sC libft/

fclean: clean
	rm -rf ${NAME}
	rm -f ${OBJS}
	make fclean -sC libft/

re: fclean all

PHONY: all clean fclean re