#include <minishell.h>

char	*cpy_character(char *str, char *new, int i)
{
	char	*chr;
	char	*temp;

	if (str[i])
	{
		chr = ft_substr(str, i, 1);
		temp = ft_strjoin(new, chr);
		free (chr);
		free (new);
		new = ft_strdup(temp);
		free (temp);
	}
	return (new);
}

static char	*cut_quotes(char *str, int i)
{
	char	*new;
	int		db_quotes;
	int		sp_quotes;

	db_quotes = 0;
	sp_quotes = 0;
	new = ft_calloc (sizeof(char *), 1);
	while (str[i])
	{
		if (str[i] == '\"' && !sp_quotes)
		{	
			db_quotes = !db_quotes;
			i++;
		}
		if (str[i] == '\'' && !db_quotes)
		{
			sp_quotes = !sp_quotes;
			i++;
		}
		new = cpy_character(str, new, i);
		if (str[i])
			i++;
	}
	free (str);
	return (new);
}

char	*handle_quotes_dollar(char *input)
{
	int	i;

	i = 0;
	if (input && ft_strchr("$", input[0]))
		input = handle_dollar(input);
	if (input && input[0] == '\'' && input[1] == '\'' && input[2] == '\0')
	{
		free (input);
		return (NULL);
	}
	if (input && input[0] == '\"' && input[1] == '\"' && input[2] == '\0')
	{
		free (input);
		return (NULL);
	}
	if (input && (ft_strchr(input, '\'') || ft_strchr(input, '\"')))
		input = cut_quotes (input, i);
	return (input);
}
