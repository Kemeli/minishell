
#include <minishell.h>

int	echo(char **cmd)
{
	int	j;
	int	new_line;

	j = 1;
	new_line = 1;
	if (!ft_strncmp(cmd[j], "-n", 3))
	{
		new_line = !new_line;
		j++;
	}
	while (cmd[j])
	{
		ft_putstr_fd (cmd[j], STDOUT_FILENO);
		ft_putstr_fd (" ", STDOUT_FILENO);
		j++;
	}
	if (new_line)
		printf("\n");
	return (1);
}

//***********************

int	pwd()
{
	char pwd[1000]; //rever isso
	getcwd(pwd, sizeof(pwd));
	printf ("%s\n", pwd);
	return (1);
}

//***********************

int	envp_print(t_list *envp_list)
{
	t_list	*aux;

	aux =  envp_list;
	while (aux)
	{
		printf("%s\n", (char *)aux->content);
		aux = aux->next;
	}
	return (1);
}

//***********************

int	cd(char **cmd, t_list *envp_list) //essa n deu pra testar, só com o loop
{
	char	*path;

	if (cmd[1] == NULL)
	{
		path = get_env("HOME", envp_list);
		if (chdir(path))
			perror("chdir");
		free (path);
	}
	else
	{
		if (chdir (cmd[1]) != 0)
			perror("chdir2"); //tirar
	}
	setenv("PWD", getcwd(NULL, 0), 1); //criar set_env;
	return (1);
}

int	exit_ms(char **cmd)
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

int	export(char **cmd, t_list *envp_list)
{
	int		i;
	int		j;
	t_list	*new;

	i = 1;
	if (!cmd[1])
		envp_print(envp_list);
	while (cmd[i])
	{
		j = 0;
		if (ft_isalpha(cmd[i][j]) || !ft_strncmp(&cmd[i][j], "_", 2))
			j++;
		else
			printf("minishell: export: `%s': not a valid identifier\n", cmd[i]); //acaba aqui
		while (cmd[i][j] && ft_strncmp(&cmd[i][j], "=", 2)) //strchr? diferente de =
		{
			if (!is_env_char(cmd[i][j]))
				printf("minishell: export: `%s': not a valid identifier\n", cmd[i]);
			j++;
		}
		if (!ft_strncmp(&cmd[i][j], "=", 2))
		{
			j++;
			if (cmd[i][j])
			{
				new = ft_lstnew(&cmd[i]);
				ft_lstadd_back(&envp_list, new);
			}
		}
		i++;
	}
	return (1);
}

int	unset(char **cmd, t_list *envp_list) //essa n deu pra testar, só com o loop
{
	t_list	*aux;
	int	check = 0;

	aux = envp_list;
	while (aux)
	{
		check = ft_strncmp(cmd[1], aux->content, ft_strlen(cmd[1]));
		if (!check)
		{
			free (aux->content);
			aux->content = ft_strdup("");
		}
		aux = aux->next;
	}
	return (1);
}

int	builtin_exec(t_exec *exec, t_list *envp_list)
{
	int	ret;

	ret = 0;
	if (exec->cmd)
	{
		if (!ft_strncmp(exec->cmd[0], "echo", 4))
			ret = echo (exec->cmd);
		else if (!ft_strncmp(exec->cmd[0], "env", 3))
			ret = envp_print(envp_list);
		else if (!ft_strncmp(exec->cmd[0], "cd", 2))
			ret = cd(exec->cmd, envp_list);
		else if (!ft_strncmp(exec->cmd[0], "pwd", 3))
			ret = pwd();
		else if (!ft_strncmp(exec->cmd[0], "export", 6))
			ret = export(exec->cmd, envp_list);
		else if (!ft_strncmp(exec->cmd[0], "exit", 4))
			ret = exit_ms(exec->cmd);
		else if (!ft_strncmp(exec->cmd[0], "unset", 5))
			ret = unset (exec->cmd, envp_list);
	}
	return (ret);
}
