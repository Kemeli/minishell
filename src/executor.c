
#include <minishell.h>

void	close_fd(int **fd)
{
	int i = 0;
	while (fd[i])
	{
		close(fd[i][0]);
		close(fd[i][1]);
		i++;
	}
	i = 3;
	while (!close(i))
		i++;
}

void	end_parent(t_exec *exec)
{
	unlink ("__heredoc");
	close_fd(exec->fd);
	free_int_mat(exec->fd);
	free_matrix(exec->envp_ms);
	free_matrix(exec->input);
}

void	exec_child(t_exec *exec, t_redirect *redir, t_token *list, t_list *envp)
{
	exec->pid = fork();
	shell.current_pid = exec->pid;
	if (exec->pid == 0)
		child(exec, redir, list, envp);
}

void	free_parent_process(t_exec *exec, t_redirect *redirect)
{
	free_matrix (exec->cmd);
	free (redirect);
	if (exec->path)
		free (exec->path);
}

void	start_exec(t_token *list, t_exec *exec, t_list *envp)
{
	t_redirect	*redir;
	int			is_builtin;

	while (exec->to_process >= 1)
	{
		redir = ft_calloc(sizeof(t_redirect), 1);
		redirector(list, redir, envp); //atualiza list em cmd_handler
		list = get_cmd_matrix(list, exec);
		is_builtin = 0;
		if (exec->ended_proc == 0 && exec->to_process == 1)
			is_builtin = try_builtin_exec(exec, &envp);
		if (!is_builtin)
			exec_child(exec, redir, list, envp);
		free_parent_process(exec, redir);
		exec->to_process--;
		exec->ended_proc++;
	}
	end_parent (exec);
	waitpid(exec->pid, 0, 0);
	waitpid(-1, NULL, 0);
	shell.current_pid = 0;
}

void	start_fd(t_exec *exec)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	exec->fd = ft_calloc(exec->to_process, sizeof(int *));
	while (i < exec->to_process)
	{
		exec->fd[j] = ft_calloc(2, sizeof(int));
		exec->fd[j][0] = -1;
		exec->fd[j][1] = -1;
		pipe(exec->fd[j++]);
		i++;
	}
}

void	execute(t_token *list, t_list *envp_list, t_exec *exec)
{
	t_token	*aux;

	exec->to_process = 1;
	aux = list;
	while (aux)
	{
		if (aux->type == PIPE)
			exec->to_process++;
		aux = aux->next;
	}
	aux = list;
	start_fd(exec);
	start_exec(list, exec, envp_list);
}
