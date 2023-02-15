
#include "minishell.h"

void	print_list(t_token *list)
{
	t_token *aux;

	aux = list;
	while (aux)
	{
		printf("cmd: %s, type: %d\n", aux->cmd, aux->type);
		aux = aux->next;
	}
}

//antes de checar isso aqui, perciso checar se está ou não entre aspas
void	get_type(t_token *token)
{
	if (!ft_strncmp(token->cmd, "<", ft_strlen(token->cmd))) //aqui o próximo é entendido como infile, tratar isso
		token->type = IN_REDIRECT;
	else if (!ft_strncmp(token->cmd, ">", ft_strlen(token->cmd))) //aqui o próximo é entendido como outfile, tratar isso
		token->type = OUT_REDIRECT;
	else if (!ft_strncmp(token->cmd, "|", ft_strlen(token->cmd)))
		token->type = PIPE;
	else if (!ft_strncmp(token->cmd, "<<", ft_strlen(token->cmd)))
		token->type = HEREDOC;
	else if (!ft_strncmp(token->cmd, ">>", ft_strlen(token->cmd)))
		token->type = APPEND;
	//falta todos os outros símbolos, quais? como?
	//falta os argumentos e comandos tb
}

t_token	*get_list(t_token *new_token, t_token *list)
{
	t_token	*aux;

	if (list == NULL) //setar como null na main, esse é o inicio da lista
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

void	lexer(char *input, t_token *list)
{
	t_token	*new;
	char	**temp;
	int		i;

	temp = ft_split(input, ' ');
	i = 0;
	while(temp[i])
	{
		new = ft_calloc(sizeof(t_token), 1);
		list = get_list(new, list);
		new->cmd = temp[i];
		if (new->prev && new->prev->type == IN_REDIRECT)
			new->type = INFILE;
		else if (new->prev && new->prev->type == OUT_REDIRECT)
			new->type = OUTFILE;
		else if (new->prev && new->prev->type == APPEND)
			new->type = OUTFILE;
		else //e o heredoc, entra aqui?
			get_type(new);
		i++;
	}
	print_list(list);
}
