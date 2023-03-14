
#include <minishell.h>

int	is_builtin(char *cmd)
{
	const char *built[6] = {"echo", "pwd", "export", "unset" , "env", "exit"};
	int i;

	i = 0;
	while (i < 6)
	{
		if (!ft_strncmp(cmd, built[i], ft_strlen(cmd)))
			return (1);
		i++;
	}
	return (0);
}

void	check_type(t_token *token)
{
	if (!ft_strncmp(token->cmd, "<", ft_strlen(token->cmd)))
		token->type = IN_REDIRECT;
	else if (!ft_strncmp(token->cmd, ">", ft_strlen(token->cmd)))
		token->type = OUT_REDIRECT;
	else if (!ft_strncmp(token->cmd, "|", ft_strlen(token->cmd)))
		token->type = PIPE;
	else if (!ft_strncmp(token->cmd, "<<", ft_strlen(token->cmd)))
		token->type = HEREDOC;
	else if (!ft_strncmp(token->cmd, ">>", ft_strlen(token->cmd)))
		token->type = APPEND;

	else if (token->prev && token->prev->type == IN_REDIRECT)
		token->type = INFILE;
	else if (token->prev && token->prev->type == OUT_REDIRECT)
		token->type = OUTFILE;
	else if (token->prev && token->prev->type == APPEND)
		token->type = APPEND_OUT;
	else if (token->prev && token->prev->type == HEREDOC)
		token->type = HERE_ARG;

	else if (token->prev && token->prev->type == SYS_CMD)
		token->type = ARGUMENT;
	else if (token->prev && token->prev->type == ARGUMENT)
		token->type = ARGUMENT;
	else if (token->prev && token->prev->type == BUILTIN)
		token->type = ARGUMENT;
	else if (is_builtin(token->cmd))
		token->type = BUILTIN;
	else
		token->type = SYS_CMD;
}

t_token	*get_list(t_token *new_token, t_token *list)
{
	t_token	*aux;

	if (list == NULL)
		list = new_token;
	else
	{
		aux = list;
		while (aux->next)
			aux = aux->next;
		aux->next = new_token;
		new_token->prev = aux;
	}
	return list;
}

/*verifica se o 2º char é envar, se sim pula para o 3º
se não verifica se é digito $1VAR=value -- $=VAr*/
char	*handle_dollar(char *input)
{
	int		i;
	char	*ret;

	i = 0;
	ret = NULL;
	if (ft_isalpha(input[1]) || !ft_strncmp(&input[1], "_", 2))
	{
		i = 2;
		while (is_env_char(input[i]))
			i++;
	}
	else if (ft_isdigit(input[1]))
		i = 2;
	if (input[i])
		ret = ft_substr (input, i, ft_strlen(input));
	free (input);
	return (ret);
}

char	*cut_quotes(char *str)
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

t_token	*lexer(char **input, t_token *list)
{
	t_token	*new;
	int		i;

	i = -1;
	while(input[++i])
	{
		input[i] = handle_quotes_dollar(input[i]);
		if (input[i])
		{
			new = ft_calloc(sizeof(t_token), 1);
			list = get_list(new, list);
			new->cmd = ft_strdup(input[i]);
			check_type(new);
		}
	}
	return (list);
}
