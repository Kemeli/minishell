
#include <minishell.h>

int	ft_env(t_list *envp_list, char **cmd)
{
	t_list	*aux;

	if (cmd && cmd[1])
	{
		printf ("minishell: ‘%s’: invalid parameter\n", cmd[1]);
		g_shell.exit_status = 127;
		return (1);
	}
	aux = envp_list;
	while (aux)
	{
		printf("%s\n", (char *)aux->content);
		aux = aux->next;
	}
	return (1);
}
