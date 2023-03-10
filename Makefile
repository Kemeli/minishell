
SRC =		main.c \
			lexer.c \
			input_handler.c \
			free.c \
			expander.c \
			quotes.c \
			sintax.c \
			executor.c \
			redirect.c \
			env.c \
			executor_utils.c \
			builtin.c \
			signals/handlers.c \
			signals/listeners.c

LIBFT =		libft/libft.a

NAME =		minishell
INCLUDES =	-I ./src/includes -I ./libft/includes
FLAGS =		-Wall -Wextra -Werror $(INCLUDES)

OBJ_DIR =	obj
OBJS =		$(addprefix $(OBJ_DIR)/,$(SRC:%.c=%.o))

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	cc $(FLAGS) $(OBJS) $(LIBFT) -lreadline -o $@

$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
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
	@$(CC) -g $(INCLUDES) $(addprefix src/,$(SRC)) $(LIBFT) -lreadline -o $(NAME)

runrl:	$(NAME)
	make
	@valgrind --suppressions=./local.supp --leak-check=full --show-leak-kinds=all ./minishell

.PHONY: all clean fclean re debug runrl
