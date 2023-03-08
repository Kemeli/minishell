
SRC =		src/main.c \
			src/lexer.c \
			src/input_handler.c \
			src/free.c \
			src/expander.c \
			src/quotes.c \
			src/sintax.c \
			src/executor.c \
			src/redirect.c \
			src/env.c \
			executor_utils.c \
			builtins.c \

LIBFT =		libft/libft.a

NAME =		minishell
FLAGS =		-Wall -Wextra -Werror -I ./src/includes -I ./libft/includes

OBJ_DIR =	obj
OBJS =		$(addprefix $(OBJ_DIR)/,$(notdir $(SRC:%.c=%.o)))

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	cc $(FLAGS) $(OBJS) $(LIBFT) -lreadline -o $@

$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(OBJ_DIR)
	cc -c $(FLAGS) $< -o $@

$(LIBFT):
	make -sC libft/

clean:
	rm -rf $(OBJ_DIR)
	make clean -sC libft/

fclean: clean
	rm -rf $(NAME)
	make fclean -sC libft/

re: fclean all

runrl:	$(NAME)
	make
	@valgrind --suppressions=./local.supp --leak-check=full ./minishell

.PHONY: all clean fclean re
