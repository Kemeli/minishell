
#include <minishell.h>

int	ft_echo(char **cmd)
{
	int	i;
	int	new_line;

	i = 1;
	new_line = 1;
	if (cmd[i])
	{
		if (!ft_strncmp(cmd[i], "-n", 3))
		{
			new_line = !new_line;
			i++;
		}
		while (cmd[i])
		{
			ft_putstr_fd (cmd[i], STDOUT_FILENO);
			i++;
			if (cmd[i])
				ft_putstr_fd (" ", STDOUT_FILENO);
		}
	}
	if (new_line)
		printf("\n");
	return (1);
}

int	ft_pwd()
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	getcwd(pwd, sizeof(pwd));
	printf ("%s\n", pwd);
	free (pwd);
	return (1);
}

int	ft_cd(char **cmd, t_list *envp_list)
{
	char	*path;

	if (cmd[1] == NULL)
	{
		path = get_env("HOME", envp_list);
		if (chdir(path))
			ft_putstr_fd("minishell: cd: no such file or directory\n", 2); //colocar argumento?
		free (path);
	}
	else
	{
		if (chdir (cmd[1]) != 0)
			ft_putstr_fd("minishell: cd: no such file or directory\n", 2); //colocar argumento?
	}
	set_pwd(envp_list);
	return (1);
}

int	ft_exit(char **cmd)
{
	int	status;

	status = 0;
	if (cmd[1] == NULL)
		exit(status);
	if (cmd[2])
	{
		printf ("exit: invalid status"); //rever
		exit(1);
	}
	status = ft_atoi(cmd[1]);
	exit(status);
}

int	try_builtin_exec(t_exec *exec, t_list **envp_list)
{
	int	ret;

	ret = 0;
	if (exec->cmd[0])
	{
		if (!ft_strncmp(exec->cmd[0], "echo", 5))
			ret = ft_echo (exec->cmd);
		else if (!ft_strncmp(exec->cmd[0], "env", 4))
			ret = ft_env(*envp_list);
		else if (!ft_strncmp(exec->cmd[0], "cd", 3))
			ret = ft_cd(exec->cmd, *envp_list);
		else if (!ft_strncmp(exec->cmd[0], "pwd", 4))
			ret = ft_pwd();
		else if (!ft_strncmp(exec->cmd[0], "export", 7))
			ret = ft_export(exec->cmd, envp_list);
		else if (!ft_strncmp(exec->cmd[0], "exit", 5))
			ret = ft_exit(exec->cmd);
		else if (!ft_strncmp(exec->cmd[0], "unset", 6))
			ret = ft_unset (exec->cmd, *envp_list);
	}
	return (ret);
}
