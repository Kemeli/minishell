char	*meta_check(char *str, char *input, t_input_utils *in)
{
	if (input[in->i] == '<' || input[i] == '>')
	{
		if (input[in->i - 1] && !space_checker(input[in->i - 1]))
			strin[in->j++] = SEPARATOR;
		str[in->j] = input[in->i];
		if (input[in->i + 1] && check_next_position(input[in->i], input[in->i + 1]))
			str[++in->j] = input[++i];
		if (input[in->i + 1] && !space_checker(input[in->i + 1]))
			str[++in->j] = SEPARATOR;
	}
	else if (input[in->i] == '|' )
	{
		if (input[in->i - 1] && !space_checker(input[in->i - 1]))
			str[in->j++] = SEPARATOR;
		strin[in->j] = input[in->i];
		if (input[in->i + 1] && !space_checker(input[in->i + 1]))
			str[++in->j] = SEPARATOR;
	}
	return (str);
}

char	*input_separator(char *input) //REFATORAR e passou as linhas
{
	t_input_utils *in = ft_calloc(sizeof(t_input_utils), 1);

	in->i = 0;
	in->j = 0;
	in->open_quotes = 0;

	str = ft_calloc (sizeof(char *), ft_strlen(input));
	while (input[in->i])
	{
		if (quote_checker(input[in->i]) && !in->open_quotes)
			in->open_quotes = 1;
		else if (quote_checker(input[in->i]) && in->open_quotes)
			in->open_quotes = 0;
		if (input[in->i] == '<' || input[in->i] == '>' || input[in->i] == '|')
			str = meta_check(str, input);
		else if (input[in->i] == SPACE && !quotes)
			str[in->j] = SEPARATOR;
		else
			str[in->j] = input[in->i];
		in->i++;
		in->j++;
	}
	return (str);
}
	