#include <minishell.h>

void	close_fd(int **fd)
{
	int	i;

	i = 0;
	while (fd[i])
	{
		close(fd[i][0]);
		close(fd[i][1]);
		i++;
	}
	i = 3;
	while (!close(i))
		i++;
}

void	start_fd(t_exec *exec)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	exec->fd = ft_calloc(exec->to_process, sizeof(int *));
	while (i < exec->to_process)
	{
		exec->fd[j] = ft_calloc(2, sizeof(int));
		exec->fd[j][0] = -1;
		exec->fd[j][1] = -1;
		pipe(exec->fd[j++]);
		i++;
	}
}

char	**envp_matrix(t_list *list_envp)
{
	int		i;
	int		size;
	char	**envp_mat;
	t_list	*aux;

	aux = list_envp;
	size = ft_lstsize(aux);
	envp_mat = ft_calloc(sizeof (char *), size + 1);
	i = 0;
	while (i < size && aux)
	{
		envp_mat[i] = ft_strdup(aux->content);
		aux = aux->next;
		i++;
	}
	envp_mat[i] = NULL;
	return (envp_mat);
}
