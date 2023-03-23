
SRC =		main.c \
			parser/lexer.c \
			parser/input_handler.c \
			parser/expander.c \
			parser/input_utils.c \
			parser/sintax.c \
			parser/env_utils.c \
			parser/lexer_utils.c \
			parser/dollar_char.c\
			executor/executor.c \
			executor/redirect.c \
			executor/heredoc.c \
			executor/executor_utils.c \
			executor/child.c \
			executor/heredoc_utils.c \
			executor/cmd_utils.c \
			executor/cmd_path.c \
			builtins/builtin.c \
			builtins/ft_cd.c \
			builtins/ft_echo.c \
			builtins/ft_env.c \
			builtins/ft_exit.c \
			builtins/ft_export.c \
			builtins/ft_pwd.c \
			builtins/ft_unset.c \
			signals/handlers.c \
			signals/listeners.c \
			free.c \

LIBFT =		libft/libft.a

NAME =		minishell
INCLUDES =	-I ./src/includes -I ./libft/includes
FLAGS =		-Wall -Wextra -Werror $(INCLUDES) -D_XOPEN_SOURCE=700

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
	@$(CC) -D_XOPEN_SOURCE=700 -g $(INCLUDES) $(addprefix src/,$(SRC)) $(LIBFT) -lreadline -o $(NAME)

runrl:	$(NAME)
	make
	@valgrind --suppressions=./local.supp --leak-check=full --show-leak-kinds=all --track-fds=yes ./minishell

.PHONY: all clean fclean re debug runrl
