
#include <minishell.h>

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
