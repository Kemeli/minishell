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

char	*input_separator(char *input, t_input_utils *in)
{
	in->str = ft_calloc (sizeof(char *), ft_strlen(input));
	while (input[in->i])
	{
		if (input[in->i] == '\'')
			in->sp_quotes = !in->sp_quotes;
		if (input[in->i] == '\"')
			in->db_quotes = !in->db_quotes;
		if (!in->db_quotes && !in->sp_quotes)
		{
			if ((input[in->i] == '<' || input[in->i] == '>'
					|| input[in->i] == '|'))
				in->str = meta_separator(in->str, input, in);
			else if (input[in->i] == SPACE && !in->db_quotes && !in->sp_quotes)
				in->str[in->j] = SEPARATOR;
			else
				in->str[in->j] = input[in->i];
		}
		else if (input[in->i] == '\'' || input[in->i] == '\"')
			in->str[in->j] = input[in->i];
		else
			in->str[in->j] = input[in->i];
		in->i++;
		in->j++;
	}
	return (in->str);
}
