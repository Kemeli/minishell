
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
	return (aux);
}


					/* REDIRECT */

void	infile_handler(char *cmd, t_redirect *redirect)
{
	redirect->infile = open(cmd, O_RDONLY, 0444);
	// dup2(redirect->infile, STDIN_FILENO);
	// close (redirect->infile);
	redirect->has_in = 1;
}

void	outfile_handler(char *cmd, t_redirect *redirect)
{
	redirect->outfile = open(cmd, O_WRONLY | O_CREAT | O_TRUNC, 0644); //verificar permissões
	// dup2(redirect->outfile, STDOUT_FILENO);
	// close (redirect->outfile);
	redirect->has_out = 1;
}
void	append_handler(char *cmd, t_redirect *redirect) //verificar permissões
{
	redirect->outfile = open(cmd, O_WRONLY | O_CREAT, 0644);
	// dup2(redirect->outfile, STDOUT_FILENO);
	// close (redirect->outfile);
	redirect->has_out = 1;
}

char *heredoc_handler(char *here_arg, t_redirect *redirect)
{
	char *prompt = ">";
	char *read;
	char *argument = ft_calloc(ft_strlen(here_arg), 1);
	char	*temp;

	while (1)
	{
		read = readline(prompt);
		if (!read)
			break;
		if (!ft_strncmp(read, here_arg, ft_strlen(here_arg)))
		{
			free(read);
			break;
		}
		temp = ft_strjoin(argument, read);
		free (argument);
		argument = ft_strjoin(temp, "\n");
		free(temp);
		free(read);
	}
	redirect->has_in = 1;
	return (argument);
}

void	redirector(t_token *aux, t_redirect *redirect) //se cmd == redirector, chama aqui
{
	char *teste;

	if (aux->type == PIPE)
		aux = (aux->next);
	while (aux && aux->type != PIPE)
	{
		if (aux->type == INFILE)
			infile_handler(aux->cmd, redirect);
		else if (aux->type == OUTFILE)
			outfile_handler(aux->cmd, redirect);
		else if (aux->next && aux->type == HEREDOC) //lembrar mandar outfile
		{
			teste = heredoc_handler(aux->next->cmd, redirect);
			printf("...teste...\n%s...teste...\n", teste); //lembrar de tirar esse print
			free (teste);
		}
		aux = (aux->next);
	}
	// free (redirect); //dar free em outro lugar
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
	if (redirect->has_in)
	{
		dup2(redirect->infile, STDIN_FILENO);
		close (redirect->infile);
	}
	if (redirect->has_out)
	{
		dup2(redirect->outfile, STDOUT_FILENO);
		close (redirect->outfile);
	}
	if (!redirect->has_out && exec->process > 1)
		dup2 (fd[i][1], STDOUT_FILENO);
	if (!redirect->has_in && i > 0) //a partir do segundo loop, pega output do pipe anterior
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
			{
				child_process(exec->fd, i, exec, redirect, envp);
			}
		}
		else
			printf ("execute builtin");
		exec->process--;
		// free (redirect); //pq o desse processe ainda existe normal
		i++;
		free (redirect);
	}
	close_fd(exec->fd);
	waitpid(exec->pid, 0, 0);
	waitpid(-1, NULL, 0);
}

void	start_exec(t_exec *exec, t_token *aux, char **envp)
{
	int	i;
	int	j;
	exec->fd = ft_calloc(exec->process, sizeof(int *));
	i = 1;

	// if (is_builtin(aux->cmd) && exec->process == 1) //é builtin e só tem um exec->processo
	// 	printf("exec_builtin(exec->cmd)\n"); //colocar a função correta aqui
		//executar uma vez só no child
	if (exec->process >= 1)
	{
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
		exec_child(aux, exec, envp); //aqui passa o começo da lista
		
		// close_fd(exec->fd);
		// waitpid(exec->pid, 0, 0);
		// waitpid(-1, NULL, 0);
	}
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