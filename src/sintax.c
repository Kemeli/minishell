
#include <minishell.h>

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
		if (aux->next && is_metachar(aux->type) && is_metachar(aux->next->type))
			printf ("minishell: syntax error near unexpected token `%s'\n", aux->next->cmd); //exit
		else if (is_metachar(aux->type) && !aux->next) //redirector sozinho ou no final do input
			printf ("minishell: syntax error near unexpected token `%s'\n", aux->cmd);
		aux = aux->next;
	}
}


//invalid envar tem que sumir
//echo + invalid envar : linha vazia
//só echo : linha vazia
//echo $dhfjdhs $jdhfjdh $kdfdgh $PATH ---- printa o path
//echo sem nada é linha vazia, então tem q chegar lá sem nada