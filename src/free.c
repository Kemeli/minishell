
#include <minishell.h>

void	free_matrix(char **input)
{
	int	i;

	i = 0;
	while (input && input[i])
	{
		free(input[i]);
		i++;
	}
	if (input)
		free(input);
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

	while(list != NULL)
	{
		aux = list;
		list = list->next;
		free(aux->cmd);
		free(aux);
	}
	free(list);
}

// void	free_list(t_list *list)
// {
// 	t_list	*aux;

// 	while(list != NULL)
// 	{
// 		aux = list;
// 		list = list->next;
// 		free(aux->content);
// 		free(aux);
// 	}
// 	free(list);
// }

// void	ft_lstclear(t_list **lst, void (*del)(void *))
// {
// 	t_list	*temporary;

// 	if (!lst || !del)
// 		return ;
// 	while (*lst)
// 	{
// 		temporary = *lst;
// 		*lst = temporary->next;
// 		del(temporary->content);
// 		free(temporary);
// 	}
// 	*lst = NULL;
// }
