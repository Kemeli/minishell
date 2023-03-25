#include <minishell.h>

int	redirector(t_token *aux, t_redirect *redir, t_list *envp)
{
	char	*file;

	if (aux->type == PIPE)
		aux = (aux->next);
	while (aux && aux->type != PIPE)
	{
		file = ft_strdup(aux->cmd);
		if (aux->type == INFILE)
		{
			redir->infile = open(file, O_RDONLY, 0444);
			if (redir->infile == -1)
			{
				perror (file);
				free (file);
				return (0);
			}
		}
		else if (aux->type == APPEND_OUT)
		{
			redir->outfile = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (redir->outfile == -1)
			{
				perror (file);
				free (file);
				return (0);
			}
		}
		else if (aux->type == OUTFILE)
		{
			redir->outfile = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (redir->outfile == -1)
			{
				perror (file);
				free (file);
				return (0);
			}
		}
		else if (aux->next && aux->type == HEREDOC)
		{
			if (!heredoc_handler(redir, envp, &aux))
			{
				free (file);
				return (0);
			}
		}
		if (aux)
			aux = (aux->next);
		free (file);
	}
	return (1);
}
