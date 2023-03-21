#include <minishell.h>

static void	end_parent(t_exec *exec)
{
	unlink ("__heredoc");
	close_fd(exec->fd);
	free_int_mat(exec->fd);
	free_matrix(exec->envp_ms);
	// free_matrix(exec->input);
}

static void	free_parent_process(t_exec *exec, t_redirect *redirect)
{
	free_matrix (exec->cmd);
	free (redirect);
	if (exec->path)
		free (exec->path);
}

static void	exec_child(
	t_exec *exec,
	t_redirect *redir,
	t_token *list,
	t_list *envp
)
{
	exec->pid = fork();
	g_shell.current_pid = exec->pid;
	if (exec->pid == 0)
		child(exec, redir, list, envp);
}

static void	execute(t_token *list, t_exec *exec, t_list *envp)
{
	t_redirect	*redir;
	int			is_builtin;
	t_token		*aux;

	aux = list;
	while (exec->to_process >= 1)
	{
		redir = ft_calloc(sizeof(t_redirect), 1);
		redirector(aux, redir, envp); //atualiza aux em cmd_handler
		aux = get_cmd_matrix(aux, exec);
		is_builtin = 0;
		if (exec->ended_proc == 0 && exec->to_process == 1)
			is_builtin = try_builtin(exec, &envp, list, redir);
		if (!is_builtin)
			exec_child(exec, redir, list, envp);
		free_parent_process(exec, redir);
		exec->to_process--;
		exec->ended_proc++;
	}
	end_parent (exec);
	// waitpid(exec->pid, 0, 0);
	// waitpid(-1, NULL, 0);
	// exec->status = 0;
	// exec->exit_status = 0;
	waitpid(exec->pid, &exec->status, 0);
	if (WIFEXITED(exec->status))
	{
		exec->exit_status = WEXITSTATUS(exec->status);
		g_shell.exit_status = exec->exit_status;
	}
	waitpid(-1, NULL, 0);
	g_shell.current_pid = 0;
}

void	start_exec(t_token *list, t_list *envp_list)
{
	t_token	*aux;
	t_exec	*exec;

	exec = ft_calloc(sizeof(t_exec), 1);
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
	execute(list, exec, envp_list);
	free (exec);
}
