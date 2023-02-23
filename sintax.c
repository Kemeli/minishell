
#include "minishell.h"

int	is_metachar(int type)
{
	if (type == IN_REDIRECT || type == OUT_REDIRECT \
		|| type == HEREDOC || type == APPEND || type == PIPE)
			return (1);
	return (0);
}

void	sintax(t_token *list)
{
	t_token	*aux;

	aux = list;
	if (aux->type == PIPE) //aqui no começo pq n pode cmeçar com pipe
		printf ("minishell: syntax error near unexpected token `%s'\n", aux->cmd);
	while (aux && aux->next)
	{
		if (is_metachar(aux->type) && is_metachar(aux->next->type))
			printf ("minishell: syntax error near unexpected token `%s'\n", aux->next->cmd);
		aux = aux->next;
	}
}

// >file - sempre cria um arquivo, menos: |>file , char invalido n nome, \/
// se tiver um builtin o proximo é considerado argumento - ja ta setado