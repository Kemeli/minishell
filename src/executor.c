
#include "../minishell.h"

void	child_process(char **cmd, char **envp, char *path)
{
	execve(path, cmd, envp);
}

void	execute(char **cmd, char **envp, char *path)
{
	int	pid;
	int	status = 0;

	pid = fork();
	if (pid == 0)
		child_process(cmd, envp, path);
	waitpid(pid, &status, 0);
}

char	**cmd_matrix(t_token *list)
{
	int	i;
	char	**cmd_n_arg = ft_calloc(sizeof(char **), 1);
	t_token *aux;

	i = 0;
	aux = list;
	cmd_n_arg = ft_calloc(sizeof(char **), 1);
	cmd_n_arg[i] = ft_strdup(aux->cmd);
	if (aux->next)
		aux = aux->next;
	while (aux && (aux->type == ARGUMENT || aux->type == HEREDOC || aux->type == HERE_ARG)) //colocar herearg como argument
	{
		cmd_n_arg[++i] = ft_strdup(aux->cmd);
		aux = aux->next;
	}
	cmd_n_arg[++i] = NULL;
	return (cmd_n_arg);
}


char	*get_path(char *cmd)
{
	int		i;
	char	*path;
	char	**paths;
	char	*env_var;
	char	*slash_cmd;

	env_var = getenv("PATH");
	paths = ft_split(env_var, ':');
	slash_cmd = ft_strjoin("/", cmd);
	i = 0;
	while (paths[i])
	{
		path = ft_strjoin(paths[i], slash_cmd);
		if (!access (path, F_OK))
			break;
		i++;
		free (path);
	}
	free_matrix (paths);
	free (slash_cmd);
	return (path);
}

void	cmd_handler(t_token *list, char **envp)
{
	char	**cmd;
	char	*path;
	t_token	*aux;

	aux = list;
	if (aux->type == SYS_CMD)
	{
		path = get_path(aux->cmd); //dar free;
		cmd = cmd_matrix(aux); //dar free
		aux = aux->next;
		execute(cmd, envp, path);
	}
}
