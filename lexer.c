
#include "minishell.h"

void	print_list(t_token *list) //essa função vai sair
{
	t_token *aux;

	aux = list;
	while (aux)
	{
		printf("cmd: %s, type: %d\n", aux->cmd, aux->type);
		aux = aux->next;
	}
}

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

//antes de checar isso aqui, perciso checar se está ou não entre aspas
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
	else if (token->prev && token->prev->type == SYS_CMD)
		token->type = ARGUMENT;
	else if (token->prev && token->prev->type == BUILTIN)
		token->type = ARGUMENT;
	else if (is_builtin(token->cmd))
		token->type = BUILTIN;
	else
		token->type = SYS_CMD;
	// else if (!ft_strncmp(token->cmd[0], "$", ft_strlen(token->cmd)))
	// 	token->type = ENV_VAR;
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

t_token	*lexer(char *input, t_token *list) //talvez refatorar aqui
{
	t_token	*new;
	char	**temp;
	int		i;

	temp = get_input_matrix(input);
	i = 0;
	while(temp[i])
	{
		new = ft_calloc(sizeof(t_token), 1);
		list = get_list(new, list);
		new->cmd = temp[i]; //talvez strdup aqui pra perder a conexão com a temp
		if (new->prev && new->prev->type == IN_REDIRECT)
			new->type = INFILE;
		else if (new->prev && new->prev->type == OUT_REDIRECT)
			new->type = OUTFILE;
		else if (new->prev && new->prev->type == APPEND)
			new->type = OUTFILE;
		else if (new->prev && new->prev->type == HEREDOC)
			new->type = HERE_ARG;
		else
			check_type(new);
		i++;
	}
	print_list(list); //tirar
	free_matrix(temp); //talvez esse free de problema na lista, talvez colocar ele no final
	return (list);
}
