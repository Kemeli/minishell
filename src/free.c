#include <minishell.h>

void	free_matrix(char **input)
{
	int	i;

	i = 0;
	while (input && input[i])
	{
		if (input && input[i])
		{
			free(input[i]);
			input[i] = NULL;
			i++;
		}
	}
	if (input)
		free(input);
	input = NULL;
}

void	free_input_matrix(char **input, int i)
{
	int counter = i;
	i = 0;
	while (counter >= 0)
	{
		if (input[i])
			free(input[i]);
		i++;
		counter--;
	}
	free (input);
}

void	free_int_mat(int **input)
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

	while (list != NULL)
	{
		aux = list;
		list = list->next;
		free(aux->cmd);
		aux->cmd = NULL;
		free(aux);
		aux = NULL;
	}
	free(list);
	list = NULL;
}
