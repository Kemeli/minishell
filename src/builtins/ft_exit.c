
#include <minishell.h>

void	free_exit(t_exec *exec, t_redirect *redir, t_token *aux, t_list *envp)
{
	if (exec->cmd)
		free_matrix(exec->cmd);
	if (exec->path)
		free (exec->path);
	if (exec->envp_ms)
		free_matrix(exec->envp_ms);
	unlink ("__heredoc");
	free_int_mat(exec->fd);
	free (redir);
	free_list (aux);
	ft_lstclear(&envp, &free);
	free (exec);
	close (0);
	close (1);
	close (2);
}

static void	exit_error(
		t_exec *exec,
		t_redirect *redir,
		t_token *list,
		t_list *envp)
{
	printf ("minishell: exited with invalid argument\n");
	free_exit (exec, redir, list, envp);
	exit (42);
}

int	ft_exit(t_exec *exec, t_token *list, t_list *envp, t_redirect *redir)
{
	int	status;
	int	i;

	status = 0;
	if (exec->cmd[1] == NULL)
	{
		free_exit (exec, redir, list, envp);
		exit(0);
	}
	if (exec->cmd[2])
		exit_error (exec, redir, list, envp);
	i = -1;
	while (exec->cmd[1][++i])
	{
		if (!ft_isdigit (exec->cmd[1][i]))
			exit_error (exec, redir, list, envp);
	}
	status = ft_atoi(exec->cmd[1]);
	free_exit (exec, redir, list, envp);
	g_shell.exit_status = status;
	exit(status);
}
