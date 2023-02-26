
#include "../minishell.h"

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
	while (aux)
	{
		if (aux->type == PIPE && !aux->next) //pipe solto
			printf("aqui a gt chama a readline novamente\n");
		else if (aux->next && is_metachar(aux->type) && is_metachar(aux->next->type))
			printf ("minishell: syntax error near unexpected token `%s'\n", aux->next->cmd); //exit
		else if (is_metachar(aux->type) && !aux->next) //redirector sozinho ou no final do input
			printf ("minishell: syntax error near unexpected token `%s'\n", aux->cmd);
		aux = aux->next;
	}
}

// >file - sempre cria um arquivo, menos: |>file , char invalido n nome, \/
// se tiver um builtin o proximo é considerado argumento - ja ta setado