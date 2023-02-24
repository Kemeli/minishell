
#include "minishell.h"


//u.file[INFILE] = open(argv[1], O_RDONLY, 0444);

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

char	*join_free(char *dst, const char *src, size_t dsize)
{
	size_t	slen;
	size_t	dlen;
	size_t	i;

	slen = ft_strlen(src);
	dlen = 0;
	while (dst[dlen] && dlen < dsize) //pega o tamanho da variavel de destino
		dlen++;
	i = 0;
	if (dlen < dsize)
	{
		while (i + dlen < (dsize - 1) && src[i])//concatena
		{
			dst[i + dlen] = src[i];
			i++;
		}
		dst[i + dlen] = '\0';
	}
	return (dst);
}

// char	*heredoc_handler(char *next_cmd) //FUNÇÃO FEIA DEMAIS, REFATORAR URGENTE!
// {
// 	char	*read;
// 	char	*argument;

// 	read = readline(">");
// 	argument = ft_strdup(read); //alloca aqui, COMO DAR FREE?
// 	argument = join_free(read, "\n", ft_strlen(argument) + 2);
// 	while (ft_strncmp(read, next_cmd, ft_strlen(next_cmd)))
// 	{
// 		free (read);
// 		read = readline(prompt);
// 		if (ft_strncmp(read, next_cmd, ft_strlen(next_cmd)))
// 		{
// 			argument = join_free(argument, read, ft_strlen(argument) + ft_strlen(read) + 1);
// 			argument = join_free(argument, "\n", ft_strlen(argument) + 2);
// 		}
// 	}
// 	return (argument);
// }

char *heredoc_handler(char *next_cmd)
{
	char *prompt = ">";
	char *read;
	char *argument = ft_calloc(ft_strlen(next_cmd), 1);
	char	*temp;

	while (1)
	{
		read = readline(prompt);
		if (!read)
			break;
		if (!ft_strncmp(read, next_cmd, ft_strlen(next_cmd)))
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
	t_redirect_utils *redirect = NULL;

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
			printf("%s", teste);
			free (teste);
		}
		aux = aux->next;
	}
}

/*
-heredoc
-- grep 'hello' <<EOF
---cat <<EOF > example.txt
---i
*/
