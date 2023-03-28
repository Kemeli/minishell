#include <minishell.h>

static char	*slash_cmd_handle(char *cmd)
{
	char	*check_slash;
	char	*absolut_cmd;
	char	*temp;

	temp = ft_strrchr(cmd, '/');
	if (temp && temp[1] != '\0')
	{
		check_slash = ft_strdup(temp);
		absolut_cmd = ft_strtrim(check_slash, "/");
		if (!access (cmd, F_OK))
		{
			free(cmd);
			cmd = ft_strdup(absolut_cmd);
		}
		free(absolut_cmd);
		free (check_slash);
	}
	return (cmd);
}

static	t_token	*cmd_matrix(t_token *aux, t_exec *exec)
{
	t_token	*cmd_list;
	int		i;
	int		count;

	count = 1;
	cmd_list = aux;
	while (cmd_list->next && cmd_list->next->type == ARGUMENT)
	{
		cmd_list = cmd_list->next;
		count++;
	}
	i = 0;
	exec->cmd = ft_calloc(sizeof(char *), count + 1);
	exec->cmd[i] = ft_strdup(aux->cmd);
	exec->cmd[i] = slash_cmd_handle(exec->cmd[i]);
	if (aux->next)
		aux = (aux->next);
	while (aux && aux->type == ARGUMENT)
	{
		exec->cmd[++i] = ft_strdup(aux->cmd);
		aux = (aux->next);
	}
	exec->cmd[++i] = NULL;
	return (aux);
}

t_token	*get_cmd_matrix(t_token *list, t_exec *exec)
{
	t_token	*aux;

	aux = list;
	if (aux && aux->type == PIPE)
		aux = aux->next;
	while (aux && aux->type != SYS_CMD)
	{
		if (aux->type == BUILTIN || aux->type == PIPE)
			break ;
		aux = aux->next;
	}
	if (aux && (aux->type == SYS_CMD || aux->type == BUILTIN))
		aux = cmd_matrix(aux, exec);
	while (aux && aux->type != PIPE)
		aux = aux->next;
	return (aux);
}
