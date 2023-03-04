

void	change_fd(int file, int std_fd)
{
	dup2(file, std_fd);
	close (file);
}

void	fd_redirect(t_redirect *redirect, )
{
	if (redirect->here_file)
		change_fd(redirect->here_file, STDIN_FILENO);
	if (redirect->infile)
		change_fd(redirect->infile, STDIN_FILENO);
	if (redirect->outfile)
		change_fd(redirect->outfile, STDOUT_FILENO);
	if (!redirect->outfile && exec->process > 1)
		dup2 (fd[i][1], STDOUT_FILENO);
	if (!redirect->infile && i > 0) //segundo loop, output pipe anterior
		dup2 (fd[i - 1][0], STDIN_FILENO);
	close_fd(fd);
}

void	child_process(int **fd, int i, t_exec *exec, t_redirect *redirect, t_token *aux)
{
	fd_redirect(redirect);
	if (exec->cmd)
		exec->path = get_path(exec->cmd[0]);
	if (exec->path)
	{
		if (execve(exec->path, exec->cmd, exec->envp_ms) == -1)
			perror(exec->cmd[0]);
	}
	else if (exec->cmd)
		exec_error(exec->cmd[0]);
	free_child (exec, redirect, aux, fd);
	exit(EXIT_FAILURE);
}
