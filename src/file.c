

char	**get_input(t_env_utils *env_var)
{
	char	*input;
	char	*temp_input;
	char	**input_matrix;
	char	*expand_input;

	temp_input = readline("minishell> "); ///CRASH se for um enter, não é null, precisa tratar, retorna empty str
	input = pipe_input(temp_input);

	int i = -1;
	int envar 0;
	while (input[++i])
	{
		if (input[i] == '$')
			envar = 1;
	}

	env_var = ft_calloc(sizeof (t_env_utils), 1); //jogar isso pra dentro da função
	if (opened_quotes(input))
	{
		ft_putstr_fd("error: opened quotes\n", 2);
		return (0);
	}
	if (envar)
		input = get_expanded_var(input, env_var);

	input_matrix = get_input_matrix(input);
	free (expand_input);
	free (input);
	return (input_matrix);
}