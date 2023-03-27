#include <minishell.h>

int	status(char *msg1, char *msg2, char *msg3, int status)
{
	ft_putstr_fd (msg1, 2);
	ft_putstr_fd (msg2, 2);
	ft_putstr_fd (msg3, 2);
	ft_putstr_fd ("\n", 2);
	g_shell.exit_status = status;
	return (0);
}

int	check_valid_envar(char **cmd, char *msg1, char *msg3, int exp)
{
	int		i;
	int		j;
	int		ret;

	i = 0;
	j = 0;
	ret = 1;
	while (cmd && cmd[++i] && cmd[i][j])
	{
		if (ft_isalpha(cmd[i][j]) || cmd[i][j] == '_')
			j++;
		else if (!status(msg1, cmd[i], msg3, 1))
			return (0);
		while (cmd[i][j] && (is_env_char(cmd[i][j]) || cmd[i][j] == '='))
		{
			if (cmd[i][j] && cmd[i][j] == '=' && exp)
				return (1);
			else if (cmd[i][j] && cmd[i][j] == '=' && !exp)
				break ;
			j++;
		}
		if (!is_env_char(cmd[i][j]) && cmd[i][j] != '\0')
			ret = status(msg1, cmd[i], msg3, 1);
	}
	return (ret);
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

int	env_built(t_exec *exec, t_list **envp, t_token *list, t_redirect *redir)
{
	int	ret;

	ret = 0;
	if (exec->cmd && exec->cmd[0])
	{
		if (!ft_strncmp(exec->cmd[0], "cd", 3))
			ret = ft_cd(exec->cmd, envp);
		else if (!ft_strncmp(exec->cmd[0], "export", 7))
			ret = ft_export(exec->cmd, envp);
		else if (!ft_strncmp(exec->cmd[0], "exit", 5))
			ret = ft_exit(exec, list, *envp, redir);
		else if (!ft_strncmp(exec->cmd[0], "unset", 6))
			ret = ft_unset (exec->cmd, *envp);
	}
	return (ret);
}
