
#include <minishell.h>

static void	set_pwd(t_list *envp_list)
{
	char	**pwd;
	char	*temp;

	temp = NULL;
	temp = getcwd (temp, BUFFER);
	pwd = ft_calloc (sizeof(char *), 3);
	pwd[0] = ft_strdup ("export");
	pwd[1] = ft_strjoin("PWD=", temp);
	pwd[2] = NULL;
	ft_export (pwd, &envp_list);
	free (temp);
	free_matrix (pwd);
}

static void	set_oldpwd(t_list **envp_list, char *temp)
{
	char	**oldpwd;

	oldpwd = ft_calloc (sizeof(char *), 3);
	oldpwd[0] = ft_strdup ("export");
	oldpwd[1] = ft_strjoin("OLDPWD=", temp);
	oldpwd[2] = NULL;
	ft_export (oldpwd, envp_list);
	free_matrix (oldpwd);
}

int	cd_error(char *msg, char *cmd)
{
	char	*new_msg;

	if (cmd)
	{
		new_msg = ft_strjoin(msg, cmd);
		perror (new_msg);
		free (new_msg);
	}
	else if (!msg)
		ft_putstr_fd("minishell: cd: HOME not available\n", 2);
	else if (!cmd)
		ft_putstr_fd (msg, 2);
	g_shell.exit_status = 1;
	return (0);
}

int	ft_cd(char **cmd, t_list **envp_list)
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
		if (!path || chdir(path))
			cd_error(NULL, NULL);
		free (path);
	}
	else if (cmd[2])
		ret = cd_error("minishell: cd: too many arguments\n", NULL);
	else if (chdir (cmd[1]) != 0)
		ret = cd_error("minishell: cd: ", cmd[1]);
	if (ret != 0)
	{
		set_oldpwd(envp_list, temp);
		set_pwd(*envp_list);
	}
	free (temp);
	return (1);
}
