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

static char	*cpy_bytes(char *temp, char *ret, char *new_input, int i)
{
	char	*sub;

	if (!ret)
		ret = ft_calloc (sizeof (char *), 1);
	sub = ft_substr (new_input, i, 1);
	temp = ft_strjoin (ret, sub);
	free (ret);
	ret = ft_strdup (temp);
	free (temp);
	free (sub);
	return (ret);
}

static char	*single_dollar(char *temp, char *ret)
{
	if (!ret)
		ret = ft_calloc (sizeof(char *), 1);
	temp = ft_strjoin(ret, "$");
	free (ret);
	ret = ft_strdup (temp);
	free (temp);
	return (ret);
}

static char	*validate_dollar(char *new_input)
{
	char	*ret;
	char	*temp;
	int		i;

	i = 0;
	ret = NULL;
	temp = NULL;
	while (new_input[i])
	{
		while (new_input[i] && new_input[i] != '$')
		{
			ret = cpy_bytes(temp, ret, new_input, i);
			i++;
		}
		if (new_input[i] && ft_strchr ("$", new_input[i]))
		{
			i++;
			if (!new_input[i] || new_input[i] == ' ')
				ret = single_dollar (temp, ret);
			else
				i = ignore_invalid_input(new_input, i);
		}
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
