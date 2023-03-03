
#include "../minishell.h"

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

void	redirector(t_token *aux, t_redirect *redirect)
{
	char *heredoc_input;

	if (aux->type == PIPE)
		aux = (aux->next);
	while (aux && aux->type != PIPE)
	{
		if (aux->type == INFILE)
			redirect->infile = open(aux->cmd, O_RDONLY, 0444);
		else if (aux->type == APPEND_OUT)
			redirect->outfile = open(aux->cmd, O_WRONLY | O_CREAT | O_APPEND, 0644); //verificar permissões
		else if (aux->type == OUTFILE)
			redirect->outfile = open(aux->cmd, O_WRONLY | O_CREAT | O_TRUNC, 0644); //verificar permissões
		else if (aux->next && aux->type == HEREDOC)
		{
			heredoc_input = heredoc_handler(aux->next->cmd);

			redirect->here_file = open ("__heredoc", O_WRONLY | O_CREAT | O_EXCL | O_TRUNC, 0777);
			ft_putstr_fd(heredoc_input, redirect->here_file);
			close (redirect->here_file);
			open ("__heredoc", O_RDONLY);
			free (heredoc_input);
		}
		aux = (aux->next);
	}
} 
