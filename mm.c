

// essa combinação funciona para cortar as aspas mas está causando segfault
char	**trim(char **input_matrix)
{
	int	i;
	char **ret = NULL;

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