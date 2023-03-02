
#include "../minishell.h"

t_token	*cmd_matrix(t_token *aux, t_exec *exec)
{
	int	i;

	i = 0;
	exec->cmd = ft_calloc(sizeof(char **), 1);
	exec->cmd[i] = ft_strdup(aux->cmd);
	if (aux->next)
		aux = (aux->next);
	while (aux && aux->type == ARGUMENT) //colocar herearg como argument
	{
		exec->cmd[++i] = ft_strdup(aux->cmd);
		aux = (aux->next);
	}
	exec->cmd[++i] = NULL;
	return (aux);
}

char	*get_path(char *cmd)
{
	int		i;
	char	*path;
	char	**paths;
	char	*slash_cmd;

	path = getenv("PATH");
	paths = ft_split(path, ':');
	slash_cmd = ft_strjoin("/", cmd);
	i = 0;
	while (paths[i])
	{
		path = ft_strjoin(paths[i], slash_cmd);
		if (!access (path, F_OK))
			break;
		i++;
		free (path); //talvez jogar esse free p cima
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
		if (aux->type == BUILTIN)
			break;
		aux = aux->next;
	}
	if (aux && (aux->type == SYS_CMD || aux->type == BUILTIN))
	{
		exec->path = get_path(aux->cmd); //dar free;
		aux = cmd_matrix(aux, exec); //dar free
	}
	while (aux && aux->type != PIPE)
		aux = aux->next;
	return (aux);
}

				/*  PROCESSES  */

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

void	child_process(int **fd, int i, t_exec *exec, t_redirect *redirect, char **envp)
{
	if (redirect->here_file)
	{
		if(dup2(redirect->here_file, STDIN_FILENO) == -1)
			printf("error");
		close (redirect->here_file);
	}
	if (redirect->infile)
	{
		dup2(redirect->infile, STDIN_FILENO);
		close (redirect->infile);
	}
	if (redirect->outfile)
	{
		dup2(redirect->outfile, STDOUT_FILENO);
		close (redirect->outfile);
	}
	if (!redirect->outfile && exec->process > 1)
		dup2 (fd[i][1], STDOUT_FILENO);
	if (!redirect->infile && i > 0) //a partir do segundo loop, pega output do pipe anterior
		dup2 (fd[i - 1][0], STDIN_FILENO);
	close_fd(fd);
	execve(exec->path, exec->cmd, envp); //copiar o envp do programa depois
	printf("erro execve\n");
	exit(0);
}

void	exec_child(t_token *list, t_exec *exec, char **envp)
{
	int	i;
	t_redirect *redirect; 
	t_token	*aux = list;

	i = 0;
	while (exec->process >= 1)
	{
		redirect = ft_calloc(sizeof(t_redirect), 1);;
		redirector(aux, redirect);//*primeiro é o ocmeço da lista, dpeois atualiza
		aux = cmd_handler(aux, exec); //recebe o ponteiro onde parou o command handler
		if (exec->path) //mudar isso
		{
			exec->pid = fork();
			if (exec->pid == 0)
				child_process(exec->fd, i, exec, redirect, envp);
		}
		else
			printf ("execute builtin");
		exec->process--;
		i++;
		free (redirect);
	}
	unlink ("__heredoc");
	close_fd(exec->fd);
	waitpid(exec->pid, 0, 0);
	waitpid(-1, NULL, 0);
}

void	start_exec(t_exec *exec, t_token *list, char **envp)
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
	exec_child(list, exec, envp); 
}

void	execute(t_token *list, char **envp)
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
	// cmd_handler(aux, exec); //aqui recebeu uma copia então n retorna a posição do aux
	start_exec(exec, aux, envp); //aqui passa o começo da lista
	free (exec);
}

//sttaus: execve travandoa após rodar o comando depois do primeiro pipe, o problema parece
//estar na conversa entre pipes, apesar de que ele recebe e roda mas aí trava e n finaliza