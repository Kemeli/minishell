

#include <minishell.h>

static int  ignore_invalid_input(char *input, int i)
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

char	*handle_dollar(char *input)
{
	int		i;
	char	*ret;
	char	*sub;

	i = 0;
	ret = NULL;
	if (!ft_strchr (input, '$'))
		return (input);
	while (input[i])
	{
		while (input[i] && input[i] != '$') //talvez ' ' tb
		{
			if (!ret)
				ret = ft_calloc (sizeof (char *), 1);
			sub = ft_substr (input, i, 1);
			ret = ft_strjoin (ret, sub);
			free (sub);
			i++;
		}
		if (input[i] && ft_strchr ("$", input[i]))
           i = ignore_invalid_input(input, i);
	}
	free (input);
	return (ret);
}

static char	*cut_quotes(char *str)
{
	int		i;
	char	*chr;
	char	*new;
	char	*temp;

	i = 0;
	if (ft_strchr(str, '\'') || ft_strchr(str, '\"'))
	{
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
	return (str);
}

char	*handle_quotes_dollar(char *input)
{
	if (input && ft_strchr("$", input[0]))
		input = handle_dollar(input);
	if (input)
		input = cut_quotes (input);
	return (input);
}