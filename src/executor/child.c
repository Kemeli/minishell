
#include <minishell.h>

void	free_exit(t_exec *exec, t_redirect *redir, t_token *aux, t_list *envp)
{
	if (exec->cmd)
		free_matrix(exec->cmd);
	if (exec->path)
		free (exec->path);
	if (exec->envp_ms)
		free_matrix(exec->envp_ms);
	free_int_mat(exec->fd);
	free (redir);
	free_list (aux);
	ft_lstclear(&envp, &free);
	free (exec);
}

static void	change_fd(int file, int std_fd)
{
	dup2(file, std_fd);
	close (file);
}

static void	fd_redir(t_redirect *redirect, t_exec *exec, int i) //mudar nome i
{
	if (redirect->here_file)
		change_fd(redirect->here_file, STDIN_FILENO);
	if (redirect->infile)
		change_fd(redirect->infile, STDIN_FILENO);
	if (redirect->outfile)
		change_fd(redirect->outfile, STDOUT_FILENO);
	if (!redirect->outfile && exec->to_process > 1)
		dup2 (exec->fd[i][1], STDOUT_FILENO);
	if (!redirect->infile && i > 0) //segundo loop, output pipe anterior
		dup2 (exec->fd[i - 1][0], STDIN_FILENO);
	close_fd(exec->fd);
}

void	child(t_exec *exec, t_redirect *redir, t_token *aux, t_list *envp)
{
	int	is_builtin;

	fd_redir(redir, exec, exec->ended_proc);
	is_builtin = try_builtin(exec, &envp, aux, redir);
	if (exec->cmd && !exec->path)
		exec->path = get_path(exec->cmd[0], envp);
	if (exec->path && !is_builtin)
	{
		exec->envp_ms = envp_matrix(envp);
		if (execve(exec->path, exec->cmd, exec->envp_ms) == -1)
			perror(exec->cmd[0]);
	}
	else if (exec->cmd && !is_builtin) //talvez uma função que faça isso
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(exec->cmd[0], 2);
		ft_putstr_fd(": no such file or directory\n", 2);
	}
	free_exit (exec, redir, aux, envp);
	exit(127);
}
