
#include <minishell.h>

int	ft_pwd(void)
{
	char	*pwd;

	pwd = NULL;
	pwd = getcwd(pwd, BUFFER);
	if (pwd == NULL)
	{
		g_shell.exit_status = 42;
		free (pwd);
		return (0);
	}
	printf ("%s\n", pwd);
	free (pwd);
	return (1);
}
