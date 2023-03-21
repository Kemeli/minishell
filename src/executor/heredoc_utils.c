#include <minishell.h>

static char	**alloc_eof(t_token *aux)
{
	t_token	*node;
	int		count;
	char	**here_args;

	node = aux;
	count = 0;
	while (node)
	{
		if (node->type == HERE_ARG)
			count++;
		node = node->next;
	}
	here_args = ft_calloc(sizeof(char *), count + 1);
	return (here_args);
}

char	**eof_matrix(t_token **aux)
{
	char	**eof_matrix;
	int		i;

	i = 0;
	eof_matrix = alloc_eof(*aux);
	if ((*aux)->type == HEREDOC)
		(*aux) = (*aux)->next;
	while (*aux)
	{
		if ((*aux)->type == HERE_ARG)
		{
			eof_matrix[i] = ft_strdup((*aux)->cmd);
			i++;
		}
		(*aux) = (*aux)->next;
	}
	eof_matrix[i] = NULL;
	return (eof_matrix);
}
