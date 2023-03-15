
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

void	end_procesess(t_exec *exec)
{
	unlink ("__heredoc");
	close_fd(exec->fd);
	free_int_mat(exec->fd);
}

void	free_child (t_exec *exec, t_redirect *redirect, t_token *aux, t_list *envp_list, char **input)
{
	if (exec->cmd)
		free_matrix(exec->cmd);
	if (exec->path)
		free (exec->path);
	free_matrix (input);
	free_int_mat(exec->fd);
	free (redirect);
	free_list (aux);
	free_matrix(exec->envp_ms);
	ft_lstclear(&envp_list, &free);
	free (exec);
}

void	exec_error(char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": no such file or directory\n", 2);
}

void	change_fd(int file, int std_fd)
{
	dup2(file, std_fd);
	close (file);
}

void	fd_redirect(t_redirect *redirect, t_exec *exec, int i) //mudar nome i
{
	if (redirect->here_file)
		change_fd(redirect->here_file, STDIN_FILENO);
	if (redirect->infile)
		change_fd(redirect->infile, STDIN_FILENO);
	if (redirect->outfile)
		change_fd(redirect->outfile, STDOUT_FILENO);
	if (!redirect->outfile && exec->process > 1)
		dup2 (exec->fd[i][1], STDOUT_FILENO);
	if (!redirect->infile && i > 0) //segundo loop, output pipe anterior
		dup2 (exec->fd[i - 1][0], STDIN_FILENO);
	close_fd(exec->fd);
}

void	child_process(int i, t_exec *exec, t_redirect *redirect, t_token *aux, t_list *envp_list, char **input)
{
	int	is_builtin;

	fd_redirect(redirect, exec, i);
	is_builtin = builtin_exec(exec, &envp_list);
	if (exec->cmd && !exec->path)
		exec->path = get_path(exec->cmd[0], envp_list);
	if (exec->path && !is_builtin)
	{
		exec->envp_ms = envp_matrix(envp_list);
		if (execve(exec->path, exec->cmd, exec->envp_ms) == -1)
			perror(exec->cmd[0]);
	}
	else if (exec->cmd && !is_builtin)
		exec_error(exec->cmd[0]);
	free_child (exec, redirect, aux, envp_list, input);
	exit(EXIT_FAILURE);
}

void	exec_child(t_token *list, t_exec *exec, t_list *envp,  char **input)
{
	int	i;
	t_redirect *redirect;
	t_token	*aux;
	int	is_builtin;

	aux = list;
	i = 0;
	while (exec->process >= 1)
	{
		redirect = ft_calloc(sizeof(t_redirect), 1);
		redirector(aux, redirect, envp); //atualiza aux em cmd_handler
		aux = cmd_handler(aux, exec);
		shell.current_command = list->cmd;
		is_builtin = 0;
		if (i == 0 && exec->process == 1)
			is_builtin = builtin_exec(exec, &envp);
		if (!is_builtin)
		{
			exec->pid = fork();
			shell.current_pid = exec->pid;
			if (exec->pid == 0)
				child_process(i, exec, redirect, list, envp, input);
		}
		free_matrix (exec->cmd);
		free (redirect);
		if (exec->path)
			free (exec->path);
		exec->process--;
		i++;
	}
	end_procesess (exec);
	waitpid(exec->pid, 0, 0);
	waitpid(-1, NULL, 0);
	shell.current_pid = 0;
}

void	start_exec(t_exec *exec, t_token *list, t_list *envp_list, char **input)
{
	int	i;
	int	j;
	exec->fd = ft_calloc(exec->process, sizeof(int *));

	i = 1;
	j = 0;
	while (i < exec->process)
	{
		exec->fd[j] = ft_calloc(2, sizeof(int));
		exec->fd[j][0] = -1;
		exec->fd[j][1] = -1;
		pipe(exec->fd[j++]);
		i++;
	}
	exec_child(list, exec, envp_list, input);
}

void	execute(t_token *list, t_list *envp_list, char **input)
{
	t_token	*aux;
	t_exec	*exec = ft_calloc(sizeof(t_exec), 1);
	exec->process = 1;
	aux = list;
	while (aux)
	{
		if (aux->type == PIPE)
			exec->process++;
		aux = aux->next;
	}
	aux = list;
	start_exec(exec, aux, envp_list, input);
	free_matrix(exec->envp_ms);
	free (exec);
}
