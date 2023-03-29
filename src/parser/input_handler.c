#include <minishell.h>

static char	**get_input_matrix(char *input)
{
	char			**input_matrix;
	char			*handled_input;
	t_input_utils	*in;

	in = ft_calloc(sizeof(t_input_utils), 1);
	if (!input)
		return (NULL);
	handled_input = input_separator(input, in);
	input_matrix = ft_split(handled_input, SEPARATOR);
	free(handled_input);
	free(in);
	return (input_matrix);
}

static int	check_opened_quotes(char *input)
{
	int	i;
	int	key_s;
	int	key_d;

	i = 0;
	key_s = 0;
	key_d = 0;
	while (input && input[i])
	{
		if (input[i] == '\'' && !key_s)
			key_s = 1;
		else if (input[i] == '\"' && !key_d)
			key_d = 1;
		else if (input[i] == '\'' && key_s)
			key_s = 0;
		else if (input[i] == '\"' && key_d)
			key_d = 0;
		i++;
	}
	if (!key_s && !key_d)
		return (0);
	ft_putstr_fd("error: opened quotes\n", 2);
	return (1);
}

static char	*check_handle_pipe(char *input)
{
	char	*rest_of_input;
	char	*join_input;
	char	*trimmed_input;

	trimmed_input = ft_strtrim(input, " ");
	if (trimmed_input[ft_strlen(trimmed_input) - 1] == '|' && trimmed_input[1])
	{
		rest_of_input = readline(">");
		join_input = ft_strjoin(input, rest_of_input);
		free (rest_of_input);
		free (input);
		input = ft_strdup(join_input);
		free (join_input);
	}
	free(trimmed_input);
	return (input);
}

char	**get_input(t_list *list_envp)
{
	char	*input;
	char	*temp_input;
	char	**input_matrix;

	temp_input = readline("minishell> ");
	if (temp_input == NULL)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		free_shell();
		exit(0);
		return (NULL);
	}
	if (!*temp_input)
		return (NULL);
	if (is_strblank(temp_input))
		return (NULL);
	add_history(temp_input);
	input = check_handle_pipe(temp_input);
	if (check_opened_quotes(input))
		return (NULL);
	input = get_expanded_var(input, list_envp, 0);
	input_matrix = get_input_matrix(input);
	free (input);
	return (input_matrix);
}
