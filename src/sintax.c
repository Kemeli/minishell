
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
	if (aux->type == PIPE)
		printf ("minishell: syntax error near unexpected token1 `%s'\n", aux->cmd); //exit
	while (aux)
	{
		if (aux->next && is_metachar(aux->type) && is_metachar(aux->next->type))
			printf ("minishell: syntax error near unexpected token2 `%s'\n", aux->next->cmd); //exit
		else if (is_metachar(aux->type) && !aux->next)
			printf ("minishell: syntax error near unexpected token3 `%s'\n", aux->cmd); //exit
		aux = aux->next;
	}
}
