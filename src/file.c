


void	pipe()
{
	//se encontrar um pipe
	int	fd[2];
	int	pid;
	int	in_fd;

	in_fd =  STDIN_FILENO;
	while()
	{
		if (pipe(fd) == -1)
			perror(/*what*/);
		if (pid = fork(fd) == -1)
			perror(/*what*/)
		else if (pid == 0)
		{
			close (fd[0]);
			dup2(in_fd, STDOUT_FILENO);
			if (exec->pipe_count) //criar essa struct
			{
				dup2(fd[1], STDOUT_FILENO);
				pipe_count--;
			}
			close (fd[1]);
			char **get_cmd = //pegar só o comando com seus argumentos dentro do pipe, e guardar a posição do proximo
		}
		close (in_fd);
		close (fd[1]);
		in_fd = fd[0];
	}
	waitpid (pid, 0, 0);
}





/*
1 checar se tem infile, ou heredoc até encontrar um infile, um pipe ou o fim do input
2 checar se tem outfile ou append até encontrar um pipe ou o fim do comando
3 Se tiver outfile antes do pipe, o pipe é "ignorado"
4 se tiver o pipe sem outfile antes, ele recebe a saída do comando e manda como entrada do próximo
5 após o pipe, checar se tem outro pipe ou saída não padrão, infile não deve ter (?)
6 executar os comandos de entre os redirecionadores, ex: cat infile | grep o | wc -l, primeiro executa o cat e só depois realiza os processos do pipe
*/

/*eu ja tenho a abertura dos fds simples e ja tenho a execução, falta o pipe e conectar o pipe com os comandos*/






#include "../minishell.h"

void	infile_handler(char *cmd, t_redirect_utils *redirect)
{
	redirect->infile = open(cmd, O_RDONLY, 0444);
	dup2(redirect->infile, STDIN_FILENO);
	close (redirect->infile);
}

void	outfile_handler(char *cmd, t_redirect_utils *redirect)
{
	redirect->outfile = open(cmd, O_WRONLY | O_CREAT | O_TRUNC, 0644); //verificar permissões
	dup2(redirect->outfile, STDOUT_FILENO);
	close (redirect->outfile);
}
void	append_handler(char *cmd, t_redirect_utils *redirect) //verificar permissões
{
	redirect->outfile = open(cmd, O_WRONLY | O_CREAT, 0644);
	dup2(redirect->outfile, STDOUT_FILENO);
	close (redirect->outfile);
}

char *heredoc_handler(char *here_arg)
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
	return (argument);
}

void	redirect(int	type) //se cmd == redirector, chama aqui
{
	char *test;
	
	if (aux->type == INFILE)
		infile_handler(aux->cmd, redirect);
	else if (aux->type == OUTFILE)
		outfile_handler(aux->cmd, redirect);
	else if (aux->next && aux->type == APPEND)
		append_handler(aux->next->cmd, redirect); //segfault, why?
	else if (aux->next && aux->type == HEREDOC) //lembrar mandar outfile
	{
		test = heredoc_handler(aux->next->cmd);
		printf("...test...\n%s...test...\n", test); //lembrar de tirar esse print
		free (test);
	}
}

void	foo()
{
	char	**cmd;
	char	*path;
	while (aux && aux->type != PIPE)
	{
		if (is_metachar(aux->cmd))
			redirect(aux->next->cmd);
		else if (aux->type == SYS_CMD)
		{
			path = get_path(aux->cmd); //dar free;
			cmd = cmd_matrix(aux); //dar free
		}
		aux = aux->next;
	}
//se tiver um outfile antes do pipe, a saida do comando é no outfile e a entrada do pipe é vazia
	if (aux->type == PIPE)
	{
		int	fd[2];
		int	pid;

		pipe (fd);
		pid = fork (fd);
		if (pid == 0)
		{
			close (fd[0]);
			dup2(in_fd, STDOUT_FILENO);
	}

}

/*primeiro abrir os arquivos antes do pipe
porem os dup só são feitos dentro do child
depois dos arquivos abertos, entrar no child
e começar s dups necessarios, executar o 1º comando, e setar a saida para o pipe
entrar no child novamente com a saida do pipe como entrada do proximo comando e os arquivos de depois do pipe ja abertos
*/