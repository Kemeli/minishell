
#include <minishell.h>

char *start_heredoc(char *eof)
{
	char *read;
	char *argument = ft_calloc(ft_strlen(eof), 1);
	char	*temp;

	while (1)
	{
		read = readline(">");
		if (!read)
			break;
		if (!ft_strncmp(read, eof, ft_strlen(eof)))
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

void	print_matrix(char **matrix, t_redirect *redirect)
{
	int	i;

	i = -1;
	while (matrix[++i])
	{
		ft_putstr_fd(matrix[i], redirect->here_file);
		ft_putstr_fd("\n", redirect->here_file);
	}
}

char	**here_input(char *input)
{
	int		i;
	char	**temp;
	char	**here_matrix;

	i = 0;
	temp = ft_split(input, '\n'); //free aqui?
	while (temp[i])
		i++;
	here_matrix = ft_calloc (sizeof(char *), i + 1);
	i= 0;
	while (temp[i])
	{
		here_matrix[i] = ft_strdup(handle_dollar(temp[i]));
		i++;
	}
	here_matrix[i] = NULL;
	return (here_matrix);
}

void	heredoc_handler(t_redirect *redirect, t_list *envp, char *eof)
{
	char	*input;
	char	**here_matrix;
	int		i;

	i = 0;
	input = start_heredoc(eof);
	redirect->here_file = open ("__heredoc", O_WRONLY | O_CREAT | O_EXCL | O_TRUNC, 0777);
	input = get_expanded_var (input, envp);
	here_matrix = here_input(input);
	while (here_matrix[i])
	{
		ft_putstr_fd(here_matrix[i], redirect->here_file);
		ft_putstr_fd("\n", redirect->here_file);
		i++;
	}
	close (redirect->here_file);
	open ("__heredoc", O_RDONLY);
}

void	redirector(t_token *aux, t_redirect *redirect, t_list *envp)
{
	if (aux->type == PIPE)
		aux = (aux->next);
	while (aux && aux->type != PIPE)
	{
		if (aux->type == INFILE)
		{
			redirect->infile = open(aux->cmd, O_RDONLY, 0444);
			if(redirect->infile == -1)
				perror (aux->cmd);
		}
		else if (aux->type == APPEND_OUT)
			redirect->outfile = open(aux->cmd, O_WRONLY | O_CREAT | O_APPEND, 0644); //verificar permissões
		else if (aux->type == OUTFILE)
			redirect->outfile = open(aux->cmd, O_WRONLY | O_CREAT | O_TRUNC, 0644); //verificar permissões
		else if (aux->next && aux->type == HEREDOC)
			heredoc_handler(redirect, envp, aux->next->cmd);
		aux = (aux->next);
	}
}
