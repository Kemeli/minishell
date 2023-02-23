
#include "minishell.h"

int	check_next_position(char first, char second)
{
	if (first == second)
		return (1);
	return (0);
}

int	space_checker(char input_position)
{
	if (input_position != ' ')
		return (0);
	return (1);
}

int	quote_checker(char input_position)
{
	if (input_position == '\'' || input_position == '\"')
		return (1);
	return (0);
}

char	*meta_check(char *str, char *input, t_input_utils *in)
{
	if (input[in->i] == '<' || input[in->i] == '>')
	{
		if (input[in->i - 1] && !space_checker(input[in->i - 1]))
			str[in->j++] = SEPARATOR;
		str[in->j] = input[in->i];
		if (input[in->i + 1] && check_next_position(input[in->i], input[in->i + 1]))
			str[++in->j] = input[++in->i];
		if (input[in->i + 1] && !space_checker(input[in->i + 1]))
			str[++in->j] = SEPARATOR;
	}
	else if (input[in->i] == '|' )
	{
		if (input[in->i - 1] && !space_checker(input[in->i - 1]))
			str[in->j++] = SEPARATOR;
		str[in->j] = input[in->i];
		if (input[in->i + 1] && !space_checker(input[in->i + 1]))
			str[++in->j] = SEPARATOR;
	}
	return (str);
}

char	*input_separator(char *input)
{
	t_input_utils	*in;
	char			*str;

	in = ft_calloc(sizeof(t_input_utils), 1);
	str = ft_calloc (sizeof(char *), ft_strlen(input));
	while (input[in->i])
	{
		if (quote_checker(input[in->i]) && !in->open_quotes)
			in->open_quotes = 1;
		else if (quote_checker(input[in->i]) && in->open_quotes)
			in->open_quotes = 0;
		if (input[in->i] == '<' || input[in->i] == '>' || input[in->i] == '|')
			str = meta_check(str, input, in);
		else if (input[in->i] == SPACE && !in->open_quotes)
			str[in->j] = SEPARATOR;
		else
			str[in->j] = input[in->i];
		in->i++;
		in->j++;
	}
	free(in);
	return (str);
}

char	**trim(char **input_matrix)
{
	int	i;
	char **ret;

	i = 0;
	while (input_matrix[i])
		i++;
	ret = malloc((i + 1) * sizeof(char *));
	ret[i] = NULL;
	i = 0;
	while (input_matrix[i])
	{
		ret[i] = ft_strtrim(input_matrix[i], "\"\'");
		i++;
	}
	return (ret);
}

char	**get_input_matrix(char *input)
{
	char	**input_matrix;
	char	*handled_input;
	char	**ret;

	handled_input = input_separator(input);
	input_matrix = ft_split(handled_input, SEPARATOR);
	ret = trim(input_matrix);
	free(handled_input);
	free_matrix(input_matrix);
	return (ret);
}

char	**get_input(t_env_utils *env_var)
{
	char	*input;
	char	*prompt;
	char	**input_matrix;

	prompt = "minishell> ";
	input = readline(prompt); ///CRASH se for um enter, não é null, precisa tratar, retorna empty str 
	env_var = ft_calloc(sizeof (t_env_utils), 1);
	if (opened_quotes(input))
	{
		ft_putstr_fd("error: opened quotes\n", 2);
		return (0);
	}
	char *input2 = get_expanded_var(input, env_var);
	input_matrix = get_input_matrix(input2);
	free (input2);
	return (input_matrix);
}
