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

static char	*heredoc(char **eof)
{
	char	*read;
	char	*input;
	int		i;

	i = 0;
	input = ft_calloc(sizeof (char *), 1);
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
	return (input);
}

static char	*start_heredoc(t_token **aux)
{
	char	*input;
	char	**eof;

	eof = eof_matrix(aux);
	set_ctrl_c_heredoc();
	input = heredoc(eof);
	set_listeners();
	free_matrix (eof);
	if (g_shell.stop_loop == 1)
	{
		free (input);
		g_shell.stop_loop = 0;
		return (NULL);
	}
	return (input);
}

int	heredoc_handler(t_redirect *redir, t_list *envp, t_token **aux)
{
	char	*input;
	char	**input_matrix;
	char	*file;

	input = start_heredoc (aux);
	if (input)
	{
		file = ft_strdup("__heredoc");
		redir->here_file = open
				(file, O_WRONLY | O_CREAT | O_EXCL | O_TRUNC, 0777);
		input = get_expanded_var (input, envp, 1);
		input_matrix = heredoc_matrix (input);
		print_heredoc (input_matrix, redir);
		free (input);
		free_matrix (input_matrix);
		close (redir->here_file);
		open (file, O_RDONLY);
		free (file);
	}
	if (!input)
		return (0);
	return (1);
}
