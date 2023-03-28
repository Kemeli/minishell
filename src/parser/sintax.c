#include <minishell.h>

static int	is_meta(int type)
{
	if (type == IN_REDIRECT || type == OUT_REDIRECT
		|| type == HEREDOC || type == APPEND || type == PIPE)
		return (1);
	return (0);
}

static int	error_sintax(char *cmd)
{
	ft_putstr_fd ("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd (cmd, 2);
	ft_putstr_fd ("'\n", 2);
	return (0);
}

int	sintax(t_token *list)
{
	t_token	*aux;
	int		check_sintax;

	aux = list;
	check_sintax = 1;
	if (aux->type == PIPE)
		return (error_sintax (aux->cmd));
	while (aux && check_sintax)
	{
		if (aux->type == PIPE && !aux->next)
			return (error_sintax (aux->cmd));
		else if (aux->type == PIPE)
			aux = aux->next;
		if (aux && aux->next && is_meta(aux->type) && is_meta(aux->next->type))
			return (error_sintax (aux->next->cmd));
		else if (aux && is_meta(aux->type) && !aux->next)
			return (error_sintax (aux->cmd));
		aux = aux->next;
	}
	return (check_sintax);
}


/*
int	sintax (char **cmd)
{
	int	i;

	i = 0
	if (cmd[0][0] == '|')
		return (error_sintax ("|"));
	while (cmd[i])
	{
		if (!ft_strncmp(cmd[i]), "|", ft_strlen(cmd[i]))
		{
			i++;
			if (!cmd[i])
				return (error_sintax ("|"));
			i--;
		}
		else if (!ft_strncmp(cmd[i]), "|", ft_strlen(cmd[i]))
			i++;
		if (cmd[i])
		{
			if (is_meta(cmd[i]))
			{
				i++;
				if (is_meta (cmd[i]))
					return (error_sintax ("|"));
				i--;
			}
		}
		else if (cmd[i] && is_meta (cmd[i]))
		{
			i++;
			if (!cmd[i])
				return (error_sintax ("|"));
		}
		i++;
	}
	return (1);
}*/