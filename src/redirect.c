
#include <minishell.h>


char	**check_more_heredoc (t_token **aux)
{
	char	**here_args;
	t_token	*node;
	int		i;
	int		count;

	node = *aux;
	count = 0;
	while (node)
	{
		if (node->type == HERE_ARG)
		count++;
		node = node->next;
	}
	i = 0;
	here_args = ft_calloc(sizeof(char *), count + 1);
	if ((*aux)->type == HEREDOC)
		(*aux) = (*aux)->next;
	while (*aux)
	{
		if ((*aux)->type == HERE_ARG)
		{
			here_args[i] = ft_strdup((*aux)->cmd);
			i++;
		}
		(*aux) = (*aux)->next;
	}
	here_args[i] = NULL;
	return (here_args);
}

char *start_heredoc(t_token **aux)
{
	char *read;
	char *argument = ft_calloc(sizeof (char *), 1);
	char	*temp;
	char	**eof;
	int		i;

	i = 0;
	eof = check_more_heredoc(aux);
	while (1)
	{
		read = readline(">");
		if (!read)
			break;
		if (eof[i] && !ft_strncmp(read, eof[i], ft_strlen(eof[i])))
		{
			i++;
			if (!eof[i])
				break;
			free(read);
			free (argument);
			argument = ft_calloc(sizeof (char *), 1);
		}
		else
		{
			temp = ft_strjoin(argument, read);
			free (argument);
			argument = ft_strjoin(temp, "\n");
			free(temp);
		}
	}
	free_matrix (eof);
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
	temp = ft_split(input, '\n');
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
	free (temp);
	return (here_matrix);
}

void	heredoc_handler(t_redirect *redirect, t_list *envp, t_token **aux)
{
	char	*input;
	char	**here_matrix;
	int		i;

	i = 0;
	input = start_heredoc(aux);
	redirect->here_file = open ("__heredoc", O_WRONLY | O_CREAT | O_EXCL | O_TRUNC, 0777);
	input = get_expanded_var (input, envp, 1);
	here_matrix = here_input(input);
	while (here_matrix[i])
	{
		ft_putstr_fd(here_matrix[i], redirect->here_file);
		ft_putstr_fd("\n", redirect->here_file);
		i++;
	}
	free (input);
	free_matrix (here_matrix);
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
			heredoc_handler(redirect, envp, &aux);
		if (aux)
			aux = (aux->next);
	}
}
