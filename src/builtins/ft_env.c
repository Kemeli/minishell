
#include <minishell.h>

int	ft_env(t_list *envp_list, char **cmd)
{
	char	**matrix;
	int		i;

	if (cmd && cmd[1])
	{
		status ("minishell: env: ‘", cmd[1], "’: invalid parameter", 127);
		return (1);
	}
	i = 0;
	matrix = envp_matrix(envp_list);
	while (matrix[i])
	{
		if (matrix[i][0] == '\0')
		{
			i++;
			continue ;
		}
		printf("%s\n", matrix[i]);
		i++;
	}
	free_matrix (matrix);
	return (1);
}
