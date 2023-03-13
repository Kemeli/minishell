
#include <minishell.h>

int	echo(char **cmd)
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

//***********************

int	pwd()
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	getcwd(pwd, sizeof(pwd));
	printf ("%s\n", pwd);
	free (pwd);
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

int	cd(char **cmd, t_list *envp_list)
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
	set_pwd(envp_list);
	return (1);
}


//***********************


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


//***********************


void	update_envp(t_list **envp, char *cmd)
{
	t_list	*node;

	node = *envp;
	while (node)
	{
		if (!ft_strncmp(cmd, node->content, ft_strlen(ft_strchr(cmd, '='))))
		{
			free (node->content);
			node->content = ft_strdup(cmd);
			return ;
		}
		node = node->next;
	}
	node = ft_lstnew(ft_strdup((char *)cmd));
	ft_lstadd_back(envp, node);
}

int	export(char **cmd, t_list **envp_list)
{
	int		i;
	int		j;

	i = 1;
	if (!cmd[1])
		envp_print(*envp_list);
	while (cmd[i])
	{
		j = 0;
		if (ft_isalpha(cmd[i][j]) || !ft_strncmp(&cmd[i][j], "_", 2))
			j++;
		else
			printf("minishell: export: `%s': not a valid identifier\n", cmd[i]); //acaba aqui
		while (cmd[i][j] && !ft_strchr("=", cmd[i][j])) 
		{
			if (!is_env_char(cmd[i][j]))
				printf("minishell: export: `%s': not a valid identifier\n", cmd[i]);
			j++;
		}
		if (ft_strchr("=", cmd[i][j]))
		{
			j++;
			if (cmd[i][j])
				update_envp(envp_list, cmd[i]);
		}
		i++;
	}
	return (1);
}


//***********************


int	unset(char **cmd, t_list *envp_list)
{
	t_list	*aux;
	int	check;
	int	i;

	i = 1;
	while (cmd[i])
	{
		aux = envp_list;
		while (aux)
		{
			check = ft_strncmp(cmd[i], aux->content, ft_strlen(cmd[1]));
			if (!check)
			{
				free (aux->content);
				aux->content = ft_strdup("");
				break ;
			}
			aux = aux->next;
		}
		i++;
	}
	return (1);
}

int	builtin_exec(t_exec *exec, t_list **envp_list)
{
	int	ret;

	ret = 0;
	if (exec->cmd)
	{
		if (!ft_strncmp(exec->cmd[0], "echo", 4))
			ret = echo (exec->cmd);
		else if (!ft_strncmp(exec->cmd[0], "env", 3))
			ret = envp_print(*envp_list);
		else if (!ft_strncmp(exec->cmd[0], "cd", 2))
			ret = cd(exec->cmd, *envp_list);
		else if (!ft_strncmp(exec->cmd[0], "pwd", 3))
			ret = pwd();
		else if (!ft_strncmp(exec->cmd[0], "export", 6))
			ret = export(exec->cmd, envp_list);
		else if (!ft_strncmp(exec->cmd[0], "exit", 4))
			ret = exit_ms(exec->cmd);
		else if (!ft_strncmp(exec->cmd[0], "unset", 5))
			ret = unset (exec->cmd, *envp_list);
	}
	return (ret);
}
