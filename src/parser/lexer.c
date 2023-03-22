#include <minishell.h>

static int	is_builtin(char *cmd)
{
	char	*built[6];
	int		i;

	built[0] = "echo";
	built[1] = "pwd";
	built[2] = "export";
	built[3] = "unset";
	built[4] = "env";
	built[5] = "exit";
	i = 0;
	while (i < 6)
	{
		if (!ft_strncmp(cmd, built[i], ft_strlen(cmd)))
			return (1);
		i++;
	}
	return (0);
}

static void	check_cmd_type(t_token *token)
{
	if (token->prev && token->prev->type == SYS_CMD)
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

static void	check_redirect_type(t_token *token)
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
}

static t_token	*get_list(t_token *new_token, t_token *list)
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
	return (list);
}

t_token	*lexer(char **input, t_token *list)
{
	t_token	*new;
	int		i;

	i = -1;
	while (input[++i])
	{
		input[i] = handle_quotes_dollar(input[i]);
		if (input[i])
		{
			new = ft_calloc(sizeof(t_token), 1);
			list = get_list(new, list);
			new->cmd = ft_strdup(input[i]);
			check_redirect_type(new);
			if (!new->type)
				check_cmd_type(new);
		}
	}
	free_input_matrix (input, i);
	return (list);
}
