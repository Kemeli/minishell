
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
			src/executor_utils.c \
			src/builtin.c \

LIBFT =		libft/libft.a

NAME =		minishell
INCLUDES =	-I ./src/includes -I ./libft/includes
FLAGS =		-Wall -Wextra -Werror $(INCLUDES)

OBJ_DIR =	obj
OBJS =		$(addprefix $(OBJ_DIR)/,$(notdir $(SRC:%.c=%.o)))

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	cc $(FLAGS) $(OBJS) $(LIBFT) -lreadline -o $@

$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(OBJ_DIR)
	cc -g -c $(FLAGS) $< -o $@

$(LIBFT):
	make -sC libft/

clean:
	rm -rf $(OBJ_DIR)
	make clean -sC libft/

fclean: clean
	rm -rf $(NAME)
	make fclean -sC libft/

re: fclean all

debug:
	@echo "Compiling..."
	@make -sC ./libft --no-print-directory
	@$(CC) -g $(INCLUDES) $(SRC) $(LIBFT) -lreadline -o $(NAME)

runrl:	$(NAME)
	make
	@valgrind --suppressions=./local.supp --leak-check=full --show-leak-kinds=all ./minishell

.PHONY: all clean fclean re debug runrl
