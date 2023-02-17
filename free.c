
#include "minishell.h"

void	free_matrix(char **input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		free(input[i]);
		i++;
	}
	free(input);
}

void	free_list(t_token *list)
{
	t_token	*aux;

	while(list != NULL)
	{
		aux = list;
		list = list->next;
		free(aux);
	}
	free(list);
}