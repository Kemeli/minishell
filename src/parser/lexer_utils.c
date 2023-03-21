#include <minishell.h>

static int	ignore_invalid_input(char *input, int i)
{
	i++;
	if (input[i] && (ft_isalpha(input[i]) || !ft_strncmp(&input[i], "_", 2)))
	{
		i++;
		while (input[i] && is_env_char(input[i]))
			i++;
	}
	else if (input[i] && ft_isdigit(input[i]))
		i++;
	return (i);
}

char	*validate_dollar(char *new_input)
{
	char	*ret;
	char	*sub;
	char	*temp;
	int		i;

	i = 0;
	ret = NULL;
	while (new_input[i])
	{
		while (new_input[i] && new_input[i] != '$') //talvez ' ' tb
		{
			if (!ret)
				ret = ft_calloc (sizeof (char *), 1);
			sub = ft_substr (new_input, i, 1);
			temp = ft_strjoin (ret, sub);
			free (ret);
			ret = ft_strdup (temp);
			free (temp);
			free (sub);
			i++;
		}
		if (new_input[i] && ft_strchr ("$", new_input[i]))
			i = ignore_invalid_input(new_input, i);
	}
	return (ret);
}

char	*handle_dollar(char *input)
{
	char	*ret;
	char	*new_input;

	new_input = ft_strdup (input);
	free (input);
	input = NULL;
	if (!ft_strchr (new_input, '$'))
		return (new_input);
	ret = validate_dollar(new_input);
	free (new_input);
	return (ret);
}

static char	*cut_quotes(char *str)
{
	int		i;
	char	*chr;
	char	*new;
	char	*temp;

	i = 0;
	if (!(ft_strchr(str, '\'') || ft_strchr(str, '\"')))
		return (str);
	new = ft_calloc (sizeof(char *), 1);
	while (str[i])
	{
		while (str[i] && ft_strchr("\"\'", str[i]))
			i++;
		if (str && str[i])
		{
			chr = ft_substr(str, i, 1);
			temp = ft_strjoin(new, chr);
			free (chr);
			free (new);
			new = ft_strdup(temp);
			free (temp);
			i++;
		}
	}
	return (new);
}

char	*handle_quotes_dollar(char *input)
{
	if (input && ft_strchr("$", input[0]))
		input = handle_dollar(input);
	if (input)
		input = cut_quotes (input);
	return (input);
}
