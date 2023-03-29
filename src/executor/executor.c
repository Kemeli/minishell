#include <minishell.h>

static void	end_parent(t_exec *exec)
{
	close_fd(exec->fd);
	free_int_mat(exec->fd);
	free_matrix(exec->envp_ms);
}

static void	free_parent_process(t_exec *exec, t_redir *redirect)
{
	if (redirect->here_file != 0 && redirect->here_file != -1)
	{
		close (redirect->here_file);
		unlink ("__heredoc");
	}
	if (redirect->outfile && redirect->outfile != -1)
		close(redirect->outfile);
	if (redirect->infile && redirect->infile != -1)
		close(redirect->infile);
	free_matrix (exec->cmd);
	exec->cmd = NULL;
	free (redirect);
	redirect = NULL;
	if (exec->path)
		free (exec->path);
}

static void	exec_child(
	t_exec *exec,
	t_redir *redir,
	t_token *list,
	t_list *envp
)
{
	exec->pid = fork();
	g_shell.current_pid = exec->pid;
	if (exec->pid == 0)
		child(exec, redir, list, envp);
}

static void	execute(t_token *list, t_exec *exec, t_list *envp, t_redir *redir)
{
	t_token		*aux;

	aux = list;
	while (exec->to_process >= 1)
	{
		redir = ft_calloc(sizeof(t_redir), 1);
		exec->valid_redir = redirector(aux, redir, envp);
		aux = get_cmd_matrix(aux, exec);
		if (exec->valid_redir && exec->valid_redir != -1)
		{
			exec->is_built = 0;
			if (exec->ended_proc == 0 && exec->to_process == 1)
				exec->is_built = env_built(exec, &envp, list, redir);
			if (!exec->is_built)
				exec_child(exec, redir, list, envp);
		}
		free_parent_process(exec, redir);
		if (exec->valid_redir == -1)
			break ;
		exec->to_process--;
		exec->ended_proc++;
	}
	end_parent (exec);
	wait_processes(exec);
	g_shell.current_pid = 0;
}

void	start_exec(t_token *list, t_list *envp_list)
{
	t_token		*aux;
	t_exec		*exec;
	t_redir		*redir;

	exec = ft_calloc(sizeof(t_exec), 1);
	exec->to_process = 1;
	aux = list;
	redir = NULL;
	while (aux)
	{
		if (aux->type == PIPE)
			exec->to_process++;
		aux = aux->next;
	}
	aux = list;
	start_fd(exec);
	execute(list, exec, envp_list, redir);
	free (exec);
}
