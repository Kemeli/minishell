
#include <minishell.h>

int	ft_env(t_list *envp_list, char **cmd)
{
	char	**matrix;
	int		i;

	i = 0;
	if (cmd && cmd[1])
	{
		status ("minishell: env: ‘", cmd[1], "’: invalid parameter", 127);
		return (1);
	}
	matrix = envp_matrix(envp_list);
	while (matrix[i])
	{
		if (matrix[i][0] == '\0')
		{
			i++;
			continue ;
		}
		ft_putendl_fd(matrix[i], 1);
		i++;
	}
	free_matrix (matrix);
	return (1);
}
