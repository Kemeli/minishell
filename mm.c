



#include "../minishell.h"


char	**cmd_matrix(t_token **list)
{
	int	i;
	char	**cmd_n_arg;
	t_token *aux;

	i = 0;
	aux = list;
	cmd_n_arg = ft_calloc(sizeof(char **), 1);
	cmd_n_arg[i] = ft_strdup(aux->cmd);
	if (aux->next)
		aux = aux->next;
	while (aux && aux->type == ARGUMENT) //colocar herearg como argument
	{
		cmd_n_arg[++i] = ft_strdup(aux->cmd);
		aux = aux->next;
	}
	cmd_n_arg[++i] = NULL;
	return (cmd_n_arg);
}

char	*get_path(char *cmd)
{
	int		i;
	char	*path;
	char	**paths;
	char	*env_var;
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

void	cmd_handler(t_token **list, char **envp)
{
	char	**cmd;
	char	*path;
	t_token	*aux;

	aux = list;
	if (aux && aux == PIPE)
		aux = aux->next;
	while (aux && aux != PIPE)
	{
		if (aux && aux->type == SYS_CMD || aux->type == BUILTIN)
		{
			path = get_path(aux->cmd); //dar free;
			cmd = cmd_matrix(aux); //dar free
			aux = aux->next;
		}
		aux = aux->next;
	}
}



					/* REDIRECT */

void	infile_handler(char *cmd, t_redirect *redirect)
{
	redirect->infile = open(cmd, O_RDONLY, 0444);
	dup2(redirect->infile, STDIN_FILENO);
	close (redirect->infile);
	redirect->has_in = 1;
}

void	outfile_handler(char *cmd, t_redirect *redirect)
{
	redirect->outfile = open(cmd, O_WRONLY | O_CREAT | O_TRUNC, 0644); //verificar permissões
	dup2(redirect->outfile, STDOUT_FILENO);
	close (redirect->outfile);
	redirect->has_out = 1;
}
void	append_handler(char *cmd, t_redirect *redirect) //verificar permissões
{
	redirect->outfile = open(cmd, O_WRONLY | O_CREAT, 0644);
	dup2(redirect->outfile, STDOUT_FILENO);
	close (redirect->outfile);
	redirect->has_out = 1;
}

char *heredoc_handler(char *here_arg, t_redirec *redirect)
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

void	redirector(t_token **aux, t_redirect *redirect) //se cmd == redirector, chama aqui
{
	char *teste;

	if (aux->type == PIPE)
		aux = aux->next;
	while (aux && aux->type != PIPE)
	{
		if (aux->type == INFILE)
			infile_handler(aux->cmd, redirect);
		else if (aux->type == OUTFILE)
			outfile_handler(aux->cmd, redirect);
		else if (aux->next && aux->type == APPEND)
			append_handler(aux->next->cmd, redirect); //segfault, why?

		else if (aux->next && aux->type == HEREDOC) //lembrar mandar outfile
		{
			teste = heredoc_handler(aux->next->cmd);
			printf("...teste...\n%s...teste...\n", teste); //lembrar de tirar esse print
			free (teste);
		}
		aux = aux->next;
	}
	// free (redirect); //dar free em outro lugar
}

				/*  PROCESSES  */

void	child_process(int fd[], int i, t_exec *exec, t_token **aux->list, t_redirec *redirect)
{
	redirector(aux->list, redirect);//*primeiro é o ocmeço da lista, dpeois atualiza
	if (!redirect->has_out && exec->process > 1)
		dup2 (fd[1], STDOUT_FILENO);
	if (!redirect->has_in && i > 0) //a partir do segundo loop, pega output do pipe anterior
		dup2 (fd[0], STDIN_FILENO);
	execve(exec->path, exec->cmd, envp) //copiar o envp do programa depois
}

void	exec_child(int *fd_pipe, t_token *aux_list, t_exec *exec)
{
	int	pid;
	int	status;
	int	i;
	t_redirect *redirect = ft_calloc(sizeof(t_redirect), 1);

	i = 0;
	while (exec->process >= 1)
	{
		if (i > 0) //segunda passada, precisa refazer o comando
		{
			free_matrix(exec->cmd);
			cmd_handler(&aux_list);
		}
		if (exec->path) //mudar isso
		{
			pid = fork();
			if (pid == 0)
				child_exec->process(fd_pipe[i], i, exec, *aux_list, redirect);//aqui passa o começo da lista e vai modificando
			waitpid(pid, status, 0);
		}
		else 
			printf ("execute builtin")
		exec->process--;
		free (redirect); //pq o desse processe ainda existe normal
		i++;
	}
}

void	start_exec(t_exec *exec, t_token *aux)
{
	int	i;
	int	**fd = ft_calloc(sizeof(int **), exec->process);

	if (!exec->path && exec->process == 1) //é builtin e só tem um exec->processo
		printf("exec_builtin(exec->cmd)"); //colocar a função correta aqui
		//executar uma vez só no child
	else if (exec->process > 1)
	{
		i = 0;
		while (i <= exec->process)
			pipe(fd[i++]);
		exec_child(fd, aux, exec); //aqui passa o começo da lista
	}
}

void	execute(t_token *list)
{
	t_token	*aux;
	t_exec	*exec;
	
	exec->process = 1;
	aux = list;
	while (aux)
	{
		if (aux->type == PIPE)
			exec->process++;
		aux = aux->next;
	}
	aux = list;
	cmd_handler(aux); //aqui recebeu uma copia então n retorna a posição do aux
	start_exec(exec, aux); //aqui passa o começo da lista
}

//ls -a | grep o