
#include <minishell.h>

int	ft_env(t_list *envp_list, char **cmd)
{
	char	**matrix;
	int		i;

	if (cmd && cmd[1])
	{
		printf ("minishell: ‘%s’: invalid parameter\n", cmd[1]);
		g_shell.exit_status = 127;
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
