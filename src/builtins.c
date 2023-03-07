
#include "../minishell.h"

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
		printf ("%s ", cmd[j]);
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

int	envp_print(char	**envp)
{
	int i = 0;

	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
	return (1);
}

//***********************

int	cd(char **cmd, char **envp) //essa n deu pra testar, só com o loop
{
	char	*path;

	if (cmd[1] == NULL)
	{
		path = get_env("HOME", envp);
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

int	export(char **cmd, char **envp)
{
	int i = 1;
	int j = 0;
	int k = 0;

	if (!cmd[1])
		envp_print(envp);

	while (envp[k])
		k++;

	if (ft_isalpha(cmd[i][j]) || !ft_strncmp(&cmd[i][j], "_", 2))
		j++;
	else
		printf("minishell: export: `%s': not a valid identifier\n", cmd[i]); //acaba aqui
	while (cmd[i])
	{
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
				envp[k++] = ft_strdup(cmd[i]);
		}
		i++;
	}
	return (1);
}

int	unset(char **cmd, char **envp) //essa n deu pra testar, só com o loop
{
	int	i = 0;
	int	check = 0;

	while (envp[i])
	{
		check = ft_strncmp(cmd[1], envp[i], ft_strlen(cmd[1]));
		if (!check)
		{
			free (envp[i]);
			envp[i] = ft_strdup("");
		}
		i++;
	}
	return (1);
}

// int	main (int argc, char **argv, char **envp)
// {
// 	// char	*teste[] = {"echo ", "-n ", "hello"};
// 	// echo (teste);

// 	//***********

// 	// pwd();

// 	//***********

// 	if (argc && argv)
// 		printf("HA");
// 	// envp_print (envp);

// 	//***********

// 	// char *cmd[] = {"cd", "..", NULL};
// 	// cd (cmd);
// }

int	builtin_exec(t_exec *exec)
{
	int	ret;
	int	size;
	
	ret = 0;
	size = ft_strlen(exec->cmd[0]);
	if (!ft_strncmp(exec->cmd[0], "echo", size))
		ret = echo (exec->cmd);
	else if (!ft_strncmp(exec->cmd[0], "env", size))
		ret = envp_print(exec->envp_ms);
	else if (!ft_strncmp(exec->cmd[0], "cd", size))
		ret = cd(exec->cmd, exec->envp_ms);
	else if (!ft_strncmp(exec->cmd[0], "pwd", size))
		ret = pwd();
	else if (!ft_strncmp(exec->cmd[0], "export", size))
		ret = export(exec->cmd, exec->envp_ms);
	else if (!ft_strncmp(exec->cmd[0], "exit", size))
		ret = exit_ms(exec->cmd);
	else if (!ft_strncmp(exec->cmd[0], "unset", size))
		ret = unset (exec->cmd, exec->envp_ms);	
	return (ret);
}

//echo