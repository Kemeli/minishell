
#include "minishell.h"

void	print_list(t_token *list)
{
	t_token *aux;

	aux = list;
	while (aux)
	{
		printf("cmd: %s, type: %s\n", aux->cmd, aux->type);
		aux = aux->next;
	}
}

void	get_type(t_token *token)
{
	if (!ft_strncmp(token->cmd, "<", ft_strlen(token->cmd))) //aqui o próximo é entendido como infile, tratar isso
		token->type = IN_REDIRECT;
	else if (!ft_strncmp(token->cmd, ">", ft_strlen(token->cmd))) //aqui o próximo é entendido como outfile, tratar isso
		token->type = OUT_REDIRECT;
	else if (!ft_strncmp(token->cmd, "|", ft_strlen(token->cmd)))
		token->type = PIPE;
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
	}
	return list;
}

void	lexer(char *input, t_token *list)
{
	t_token	*new_token;
	char	**temp;
	int		i;

	temp = ft_split(input, ' ');
	i = 0;
	while(temp[i])
	{
		new_token = ft_calloc(sizeof(t_token), 1);
		new_token->cmd = temp[i];
		get_type(new_token);
		list = get_list(new_token, list);
		i++;
	}
	print_list(list);
}
