
#include <minishell.h>

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

int	ft_export(char **cmd, t_list **envp_list)
{
	int		i;
	int		j;

	i = 1;
	if (!check_valid_envar(cmd, "minishell: export: `",
			"': not a valid identifier", 1))
		return (1);
	if (!cmd[1])
		ft_env(*envp_list, NULL);
	while (cmd[i])
	{
		j = 0;
		while (cmd[i][j] && !ft_strchr("=", cmd[i][j]))
			j++;
		if (ft_strchr("=", cmd[i][j]) && !ft_strchr("\0", cmd[i][j]))
		{
			if (cmd[i] && cmd[i][j])
				update_envp(envp_list, cmd[i]);
		}
		i++;
	}
	return (1);
}
