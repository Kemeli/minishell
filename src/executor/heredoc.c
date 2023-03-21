#include <minishell.h>

static void	print_heredoc(char **matrix, t_redirect *redirect)
{
	int	i;

	i = -1;
	while (matrix[++i])
	{
		ft_putstr_fd(matrix[i], redirect->here_file);
		ft_putstr_fd("\n", redirect->here_file);
	}
}

static char	**heredoc_matrix(char *input)
{
	int		i;
	char	**temp;
	char	**here_matrix;

	i = 0;
	temp = ft_split(input, '\n');
	while (temp[i])
		i++;
	here_matrix = ft_calloc (sizeof(char *), i + 1);
	i = 0;
	while (temp[i])
	{
		here_matrix[i] = ft_strdup(handle_dollar(temp[i]));
		i++;
	}
	here_matrix[i] = NULL;
	free_matrix (temp);
	return (here_matrix);
}

static char	*join_heredoc_input(char *input, char *read)
{
	char	*temp;

	temp = ft_strjoin(input, read);
	free (input);
	input = ft_strjoin(temp, "\n");
	free(temp);
	return (input);
}

void	interrupt_handler(int sig)
{
	(void) sig;
	g_shell.stop_loop = 1;
}

static char	*start_heredoc(t_token **aux)
{
	char	*read;
	char	*input;
	char	**eof;
	int		i;

	i = 0;
	input = ft_calloc(sizeof (char *), 1);
	eof = eof_matrix(aux);
	signal(SIGINT, interrupt_handler);
	while (!g_shell.stop_loop)
	{
		read = readline(">");
		if (!read)
			break ;
		if (eof[i] && !ft_strncmp(read, eof[i], ft_strlen(eof[i])))
		{
			if (!eof[++i])
				break ;
			free(read);
		}
		else
			input = join_heredoc_input(input, read);
	}
	set_listeners();
	g_shell.stop_loop = !g_shell.stop_loop;
	free_matrix (eof);
	return (input);
}

void	heredoc_handler(t_redirect *redir, t_list *envp, t_token **aux)
{
	char	*input;
	char	**input_matrix;
	char	*file;

	file = ft_strdup("__heredoc");
	redir->here_file = open (file, O_WRONLY | O_CREAT | O_EXCL | O_TRUNC, 0777);
	input = start_heredoc (aux);
	input = get_expanded_var (input, envp, 1);
	input_matrix = heredoc_matrix (input);
	print_heredoc (input_matrix, redir);
	free (input);
	free_matrix (input_matrix);
	close (redir->here_file);
	open (file, O_RDONLY);
	free (file);
}
