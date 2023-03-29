#include <minishell.h>

int	file_error(char *file)
{
	ft_putstr_fd ("minishell: ", 2);
	perror (file);
	free (file);
	return (0);
}

int	open_file(t_token *node, char *file_name, t_redir *redir)
{
	if (node->type == INFILE)
	{
		redir->infile = open(file_name, O_RDONLY, 0444);
		if (redir->infile == -1)
			return (file_error (file_name));
	}
	else if (node->type == APPEND_OUT)
	{
		redir->outfile = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (redir->outfile == -1)
			return (file_error (file_name));
	}
	else if (node->type == OUTFILE)
	{
		redir->outfile = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (redir->outfile == -1)
			return (file_error (file_name));
	}
	return (1);
}

int	redirector(t_token *aux, t_redir *redir, t_list *envp)
{
	char	*file_name;

	if (aux->type == PIPE)
		aux = (aux->next);
	while (aux && aux->type != PIPE)
	{
		file_name = ft_strdup(aux->cmd);
		if (!open_file(aux, file_name, redir))
			return (0);
		if (aux->next && aux->type == HEREDOC)
		{
			if (!heredoc_handler(redir, envp, &aux))
			{
				free (file_name);
				if (redir->here_sig == -1)
					return (-1);
				return (0);
			}
		}
		if (aux)
			aux = (aux->next);
		free (file_name);
	}
	return (1);
}
