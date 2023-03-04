

#include "../minishell.h"

char	**envp_matrix(char **envp)
{
	int	i;
	char **envp_mat;

	i = 0;
	while (envp[i])
		i++;
	envp_mat = ft_calloc(sizeof (char *), i + 1);
	i = -1;
	while (envp[++i])
		envp_mat[i] = ft_strdup(envp[i]);
	envp_mat[i] = NULL;
	return (envp_mat);
}