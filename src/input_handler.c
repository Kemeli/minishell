
#include <minishell.h>

char	**get_input_matrix(char *input)
{
	char	**input_matrix;
	char	*handled_input;

	handled_input = input_separator(input);
	input_matrix = ft_split(handled_input, SEPARATOR);
	free(handled_input);
	return (input_matrix);
}

int	opened_quotes(char *input)
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
	if (key_s || key_d)
		return (1);
	return (0);
}

char	*pipe_input(char *input)
{
	char	*rest_of_input;
	char	*join_input;

	if (input[ft_strlen(input) - 1] == '|')
	{
		rest_of_input = readline(">");
		join_input = ft_strjoin(input, rest_of_input);
		free (rest_of_input);
		free (input);
		input = ft_strdup(join_input);
		free (join_input);
	}
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
		free_shell();
		exit(0);
		return (NULL);
	}
	if (!*temp_input)
		return (NULL);
	add_history(temp_input);
	input = pipe_input(temp_input);
	if (opened_quotes(input))
	{
		ft_putstr_fd("error: opened quotes\n", 2);
		return (0); //exit com free
	}
	input = get_expanded_var(input, list_envp, 0);
	input_matrix = get_input_matrix(input);
	free (input);
	return (input_matrix);
}
