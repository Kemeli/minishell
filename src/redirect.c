
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

void	redirector(t_token *list) //se cmd == redirector, chama aqui
{
	char *teste;
	t_token	*aux;
	t_redirect_utils *redirect = ft_calloc(sizeof(t_redirect_utils), 1);

	aux = list;
	while (aux)
	{
		if (aux->type == INFILE)
			infile_handler(aux->cmd, redirect);
		else if (aux->type == OUTFILE)
			outfile_handler(aux->cmd, redirect);
		else if (aux->next && aux->type == APPEND)
			append_handler(aux->next->cmd, redirect); //segfault, why?

		else if (aux->next && aux->type == HEREDOC) //lembrar mandar outfile
		{
			teste = heredoc_handler(aux->next->cmd);
			printf("...teste...\n%s...teste...\n", teste); //lembrar de tirar esse print
			free (teste);
		}
		aux = aux->next;
	}
	free (redirect);
}

/*
-heredoc
-- grep 'hello' <<EOF
---cat <<EOF > example.txt
---i
*/
