

#include <minishell.h>

t_token	*cmd_matrix(t_token *aux, t_exec *exec)
{
	int	i;
	t_token	*cmd_list;
	int count;
	char *absolut_cmd;
	char *check_slash;

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
	check_slash = ft_strrchr(exec->cmd[i], '/'); //aqui checa se é caminho relativo
	if (check_slash)
	{
		exec->path = ft_strdup(aux->cmd);
		absolut_cmd = ft_strtrim(check_slash, "/");
		free(exec->cmd[i]);
		exec->cmd[i] = ft_strdup(absolut_cmd);
		free (absolut_cmd);
	}
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
	char	*path;
	char	**paths;
	char	*slash_cmd;
	char	*aux;

	aux = get_env("PATH", envp_list);
	paths = ft_split(aux, ':');
	free (aux);
	slash_cmd = ft_strjoin("/", cmd);
	i = 0;
	while (paths[i])
	{
		path = ft_strjoin(paths[i], slash_cmd);
		if (!access (path, F_OK))
			break;
		i++;
		free (path); //talvez jogar esse free p cima
		path = NULL;
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
