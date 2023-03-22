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

int	status(char *msg1, char *msg2, char *msg3, int status)
{
	printf ("%s", msg1);
	printf ("%s", msg2);
	printf ("%s", msg3);
	printf ("\n");
	g_shell.exit_status = status;
	return (0);
}

void	set_oldpwd(t_list **envp_list, char *temp)
{
	char	**oldpwd;

	oldpwd = ft_calloc (sizeof(char *), 3);
	oldpwd[0] = ft_strdup ("export");
	oldpwd[1] = ft_strjoin("OLDPWD=", temp);
	oldpwd[2] = NULL;
	ft_export (oldpwd, envp_list);
	free_matrix (oldpwd);
}

int	ft_cd(char **cmd, t_list **envp_list) //setar oldpwd?
{
	char	*path;
	char	*temp;
	int		ret;

	ret = 1;
	temp = NULL;
	temp = getcwd (temp, BUFFER);
	if (cmd[1] == NULL)
	{
		path = get_env("HOME", *envp_list);
		if (chdir(path))
			ret = status("minishell: ", "cd: ", "no such file or directory", 1);
		free (path);
	}
	else if (cmd[2])
		ret = status("minishell: ", "cd: ", "too many arguments", 1);
	else if (chdir (cmd[1]) != 0)
		ret = status("minishell: ", "cd: ", "no such file or directory", 1);
	if (ret != 0)
	{
		set_oldpwd(envp_list, temp);
		set_pwd(*envp_list);
	}
	free (temp);
	return (1);
}

int	ft_exit(t_exec *exec, t_token *list, t_list *envp, t_redirect *redir)
{
	int	status;
	int	i;

	status = 0;
	if (exec->cmd[1] == NULL)
	{
		free_exit (exec, redir, list, envp);
		exit(0);
	}
	if (exec->cmd[2])
	{
		printf ("minishell: exited with too many arguments\n"); //rever
		free_exit (exec, redir, list, envp);
		exit(42);
	}
	i = -1;
	while (exec->cmd[1][++i])
	{
		if (!ft_isdigit (exec->cmd[1][i]))
		{
			printf ("minishell: exited with invalid argument\n");
			free_exit (exec, redir, list, envp);
			exit(42);
		}
	}
	status = ft_atoi(exec->cmd[1]);
	free_exit (exec, redir, list, envp);
	g_shell.exit_status = status;
	exit(status);
}

int	try_builtin(t_exec *exec, t_list **envp, t_token *list, t_redirect *redir)
{
	int	ret;

	ret = 0;
	if (exec->cmd && exec->cmd[0])
	{
		if (!ft_strncmp(exec->cmd[0], "echo", 5))
			ret = ft_echo (exec->cmd);
		else if (!ft_strncmp(exec->cmd[0], "env", 4))
			ret = ft_env(*envp, exec->cmd);
		else if (!ft_strncmp(exec->cmd[0], "cd", 3))
			ret = ft_cd(exec->cmd, envp);
		else if (!ft_strncmp(exec->cmd[0], "pwd", 4))
			ret = ft_pwd();
		else if (!ft_strncmp(exec->cmd[0], "export", 7))
			ret = ft_export(exec->cmd, envp);
		else if (!ft_strncmp(exec->cmd[0], "exit", 5))
			ret = ft_exit(exec, list, *envp, redir);
		else if (!ft_strncmp(exec->cmd[0], "unset", 6))
			ret = ft_unset (exec->cmd, *envp);
	}
	return (ret);
}
