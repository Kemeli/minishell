

#include <minishell.h>

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

char	*get_env(char *var, char **envp) //mudar envp meu
{
	int		i;
	char	*expanded;
	char	*temp;
	int		check;

	i = 0;
	while (envp[i])
	{
		check = ft_strncmp(var, envp[i], ft_strlen(var));
		if (!check) //ft
		{
			temp = ft_strdup (envp[i]);
			expanded = ft_substr (temp, ft_strlen(var) + 1, ft_strlen(temp));
			free (temp);
		}
		i++;
	}
	return (expanded); //rever
}
