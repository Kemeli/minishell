#include <minishell.h>

static char	*check_executable(char *cmd)
{
	char	*curr_dir;
	char	*path;

	curr_dir = getcwd(NULL, 0);
	getcwd(curr_dir, sizeof(curr_dir));
	path = ft_strjoin(curr_dir, cmd);
	free (curr_dir);
	if (!access (path, F_OK))
		return (path);
	free (path);
	return (NULL);
}

static char	*check_acess(char *path, char **paths, char *slash_cmd)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		path = ft_strjoin(paths[i], slash_cmd);
		if (!access (path, F_OK))
			return (path);
		i++;
		free (path);
		path = NULL;
	}
	return (NULL);
}

char	*get_path(char *cmd, t_list *envp_list)
{
	char	*path;
	char	**paths;
	char	*slash_cmd;
	char	*aux;

	path = NULL;
	aux = get_env("PATH", envp_list);
	if (aux && cmd)
	{
		paths = ft_split(aux, ':');
		free (aux);
		slash_cmd = ft_strjoin("/", cmd);
		if (!ft_strchr(cmd, '/'))
			path = check_acess(path, paths, slash_cmd);
		if (!path)
			path = check_executable(slash_cmd);
		free_matrix (paths);
		free (slash_cmd);
	}
	return (path);
}
