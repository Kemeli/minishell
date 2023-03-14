
#include <minishell.h>

char *heredoc_handler(char *here_arg)
{
	char *read;
	char *argument = ft_calloc(ft_strlen(here_arg), 1);
	char	*temp;

	while (1)
	{
		read = readline(">");
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

char	**heredoc_input_handler(char *input)
{
	int		i;
	char	**temp;
	char	**heredoc_matrix;

	i = 0;
	temp = ft_split(input, '\n');
	while (temp[i])
		i++;
	heredoc_matrix = ft_calloc (sizeof(char *), i + 1);
	i= 0;
	while (temp[i])
	{
		heredoc_matrix[i] = ft_strdup(handle_dollar(temp[i]));
		i++;
	}
	heredoc_matrix[i] = NULL;
	
	// free_matrix(heredoc_matrix);
	// free_matrix(temp);
	return (heredoc_matrix);
}

void	redirector(t_token *aux, t_redirect *redirect, t_list *envp)
{
	char	*input;
	char	**heredoc_matrix;

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
		{
			input = heredoc_handler(aux->next->cmd);
			redirect->here_file = open ("__heredoc", O_WRONLY | O_CREAT | O_EXCL | O_TRUNC, 0777);
			input = get_expanded_var (input, envp);
			heredoc_matrix = heredoc_input_handler(input);
			int	i = 0;
			// while (heredoc_matrix[i])
			// {
			// 	heredoc_matrix[i] = handle_dollar(heredoc_matrix[i]);
			// 	i++;
			// }
			// i = 0;
			while (heredoc_matrix[i])
			{
				ft_putstr_fd(heredoc_matrix[i], redirect->here_file);
				ft_putstr_fd("\n", redirect->here_file);
				i++;
			}
			
			close (redirect->here_file);
			open ("__heredoc", O_RDONLY);
			// free (input);
		}
		aux = (aux->next);
	}
}
