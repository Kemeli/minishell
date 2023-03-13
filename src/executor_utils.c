
#include <minishell.h>

// char	*slash_cmd_handle(char *cmd, t_list *envp)
// {
// 	char	*check_slash;
// 	char	*absolut_cmd;
// 	char	*test;

// 	check_slash = ft_strrchr(cmd, '/'); //aqui checa se é caminho relativo
// 	if (check_slash)
// 	{
// 		absolut_cmd = ft_strtrim(check_slash, "/");
// 		test = get_path(absolut_cmd, envp);
// 		if (test != NULL)
// 		{
// 			free(cmd);
// 			cmd = ft_strdup(absolut_cmd);
// 		}
// 		free (absolut_cmd);
// 		free (test);
// 	}
// 	return (cmd);
// }

char	*slash_cmd_handle(char *cmd)
{
	char	*check_slash;
	char	*absolut_cmd;

	check_slash = ft_strdup(ft_strrchr(cmd, '/')); //aqui checa se é caminho relativo
	if (check_slash)
	{
		absolut_cmd = ft_strtrim(check_slash, "/");
		if (!access (cmd, F_OK))
		{
			free(cmd);
			cmd = ft_strdup(absolut_cmd);
		}
		free(absolut_cmd);
	}
	free (check_slash);
	return (cmd);
}

t_token	*cmd_matrix(t_token *aux, t_exec *exec)
{
	t_token	*cmd_list;
	int		i;
	int		count;
	
	count = 1;
	cmd_list = aux;
	while (cmd_list->next && cmd_list->next->type == ARGUMENT)
	{
		cmd_list = cmd_list->next;
		count++;
	}
	i = 0;
	exec->cmd = ft_calloc(sizeof(char *), count + 1);
	exec->cmd[i] = ft_strdup(aux->cmd);
	exec->cmd[i] = slash_cmd_handle(exec->cmd[i]);
	if (aux->next)
		aux = (aux->next);
	while (aux && aux->type == ARGUMENT)
	{
		exec->cmd[++i] = ft_strdup(aux->cmd);
		aux = (aux->next);
	}
	exec->cmd[++i] = NULL;
	return (aux);
}

char	*get_path(char *cmd, t_list *envp_list)
{
	int		i;
	char	*path = NULL;
	char	**paths;
	char	*slash_cmd;
	char	*aux;

	aux = get_env("PATH", envp_list);
	paths = ft_split(aux, ':');
	free (aux);
	slash_cmd = ft_strjoin("/", cmd);
	i = 0;
	if (!ft_strchr(cmd, '/'))
	{
		while (paths[i])
		{
			path = ft_strjoin(paths[i], slash_cmd);
			if (!access (path, F_OK))
				break;
			i++;
			free (path); //talvez jogar esse free p cima
			path = NULL;
		}
	}
	free_matrix (paths);
	free (slash_cmd);
	return (path);
}

t_token	*cmd_handler(t_token *list, t_exec *exec)
{
	t_token	*aux;

	aux = list;

	if (aux && aux->type == PIPE)
		aux = aux->next;
	while (aux && aux->type != SYS_CMD)
	{
		if (aux->type == BUILTIN || aux->type == PIPE)
			break;
		aux = aux->next;
	}
	if (aux && (aux->type == SYS_CMD || aux->type == BUILTIN))
		aux = cmd_matrix(aux, exec); //dar free
	while (aux && aux->type != PIPE)
		aux = aux->next;
	return (aux);
}
