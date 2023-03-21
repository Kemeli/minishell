#include <minishell.h>

static int	is_meta(int type)
{
	if (type == IN_REDIRECT || type == OUT_REDIRECT
		|| type == HEREDOC || type == APPEND || type == PIPE)
		return (1);
	return (0);
}

static int	error_sintax(char *cmd)
{
	printf ("minishell: syntax error near unexpected token `%s'\n", cmd);
	return (0);
}

int	sintax(t_token *list)
{
	t_token	*aux;
	int		check_sintax;

	aux = list;
	check_sintax = 1;
	if (aux->type == PIPE)
		check_sintax = error_sintax (aux->cmd);
	while (aux && check_sintax)
	{
		if (aux->next && is_meta(aux->type) && is_meta(aux->next->type))
			check_sintax = error_sintax (aux->next->cmd);
		else if (is_meta(aux->type) && !aux->next)
			check_sintax = error_sintax (aux->cmd);
		aux = aux->next;
	}
	return (check_sintax);
}
