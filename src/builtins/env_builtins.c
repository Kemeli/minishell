#include <minishell.h>

int	ft_env(t_list *envp_list, char **cmd)
{
	t_list	*aux;

	if (cmd && cmd[1])
	{
		printf ("minishell: ‘%s’: No such file or directory\n", cmd[1]);
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

int	ft_unset(char **cmd, t_list *envp_list)
{
	t_list	*aux;
	int		check;
	int		i;
	int		j;

	i = 1;
	j = 1;
	while (cmd[i])
	{
		if (ft_isalpha(cmd[i][0] && cmd[i][0] == '_'))
		{
			while (!is_env_char(cmd[i][j]))
				j++;
			if (!is_env_char(cmd[i][j]))
			{
				printf("minishell: unset: `%s': not a valid identifier\n", cmd[i]);
				g_shell.exit_status = 1;
				return (1);
			}
		}
		else
		{
			printf("minishell: unset: `%s': not a valid identifier\n", cmd[i]);
			g_shell.exit_status = 1;
			return (1);
		}

	}
	i = 0;
	while (cmd[i])
	{
		aux = envp_list;
		while (aux)
		{
			check = ft_strncmp(cmd[i], aux->content, ft_strlen(cmd[i]));
			if (check == 0)
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

static void	update_envp(t_list **envp, char *cmd)
{
	t_list	*node;
	int		i;

	i = 0;
	node = *envp;
	while (cmd[i] != '=')
		i++;
	while (node)
	{
		if (!ft_strncmp(cmd, node->content, i))
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

int	ft_export(char **cmd, t_list **envp_list) //refatorar
{
	int		i;
	int		j;

	i = 1;
	if (!cmd[1])
		ft_env(*envp_list, NULL);
	while (cmd[i])
	{
		j = 0;
		if (ft_isalpha(cmd[i][j]) || !ft_strncmp(&cmd[i][j], "_", 2))
			j++;
		else
		{
			printf("minishell: export: `%s': not a valid identifier\n", cmd[i]); //acaba aqui
			g_shell.exit_status = 1;
			return (1);
		}
		while (cmd[i][j] && !ft_strchr("=", cmd[i][j]))
		{
			if (!is_env_char(cmd[i][j]))
			{
				printf("minishell: export: `%s': not a valid identifier\n", cmd[i]);
				g_shell.exit_status = 1;
				return (1);
			}
			j++;
		}
		if (ft_strchr("=", cmd[i][j]) && !ft_strchr("\0", cmd[i][j]))
		{
			if (cmd[i] && cmd[i][j])
				update_envp(envp_list, cmd[i]);
		}
		i++;
	}
	return (1);
}
