#include <minishell.h>

static int	check_next_pos(char first, char second)
{
	if (first == second)
		return (1);
	return (0);
}

static int	space_checker(char input_position)
{
	if (input_position != ' ')
		return (0);
	return (1);
}

static int	quote_checker(char input_position)
{
	if (input_position == '\'' || input_position == '\"')
		return (1);
	return (0);
}

static char	*meta_separator(char *str, char *input, t_input_utils *in)
{
	if (input[in->i] == '<' || input[in->i] == '>')
	{
		if (in->i > 0 && !space_checker(input[in->i - 1]))
			str[in->j++] = SEPARATOR;
		str[in->j] = input[in->i];
		if (input[in->i + 1] && check_next_pos(input[in->i], input[in->i + 1]))
			str[++in->j] = input[++in->i];
		if (input[in->i + 1] && !space_checker(input[in->i + 1]))
			str[++in->j] = SEPARATOR;
	}
	else if (input[in->i] == '|' )
	{
		if (in->i > 0 && !space_checker(input[in->i - 1]))
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
			str = meta_separator(str, input, in);
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
