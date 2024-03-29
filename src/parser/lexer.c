/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaiane- < kdaiane-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 20:12:56 by kdaiane-          #+#    #+#             */
/*   Updated: 2023/03/30 20:12:57 by kdaiane-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	is_builtin(char *cmd)
{
	char	*built[6];
	int		i;

	built[0] = "echo";
	built[1] = "pwd";
	built[2] = "export";
	built[3] = "unset";
	built[4] = "env";
	built[5] = "exit";
	i = 0;
	while (i < 6)
	{
		if (!ft_strncmp(cmd, built[i], ft_strlen(cmd)))
			return (1);
		i++;
	}
	return (0);
}

static void	check_cmd_type(t_token *token)
{
	if (token->prev && token->prev->type == SYS_CMD)
		token->type = ARGUMENT;
	else if (token->prev && token->prev->type == ARGUMENT)
		token->type = ARGUMENT;
	else if (token->prev && token->prev->type == BUILTIN)
		token->type = ARGUMENT;
	else if (is_builtin(token->cmd))
		token->type = BUILTIN;
	else if (token->cmd[0] != '\0')
		token->type = SYS_CMD;
}

static void	check_redirect_type(t_token *token)
{
	int	len;

	len = ft_strlen(token->cmd);
	if (!ft_strncmp(token->cmd, "<", len) && token->cmd[0] != '\0')
		token->type = IN_REDIRECT;
	else if (!ft_strncmp(token->cmd, ">", len) && token->cmd[0] != '\0')
		token->type = OUT_REDIRECT;
	else if (!ft_strncmp(token->cmd, "|", len) && token->cmd[0] != '\0')
		token->type = PIPE;
	else if (!ft_strncmp(token->cmd, "<<", len) && token->cmd[0] != '\0')
		token->type = HEREDOC;
	else if (!ft_strncmp(token->cmd, ">>", len) && token->cmd[0] != '\0')
		token->type = APPEND;
	else if (token->prev && token->prev->type == IN_REDIRECT)
		token->type = INFILE;
	else if (token->prev && token->prev->type == OUT_REDIRECT)
		token->type = OUTFILE;
	else if (token->prev && token->prev->type == APPEND)
		token->type = APPEND_OUT;
	else if (token->prev && token->prev->type == HEREDOC)
		token->type = HERE_ARG;
}

static t_token	*get_list(t_token *new_token, t_token *list)
{
	t_token	*aux;

	if (list == NULL)
		list = new_token;
	else
	{
		aux = list;
		while (aux->next)
			aux = aux->next;
		aux->next = new_token;
		new_token->prev = aux;
		new_token->next = NULL;
	}
	return (list);
}

t_token	*lexer(char **input, t_token *list)
{
	t_token	*new;
	int		i;

	i = -1;
	while (input[++i])
	{
		input[i] = handle_dollar(input[i]);
		if (input[i])
		{
			new = ft_calloc(sizeof(t_token), 1);
			list = get_list(new, list);
			new->cmd = ft_strdup(input[i]);
			check_redirect_type(new);
			if (!new->type)
				check_cmd_type(new);
			if (!new->type)
				new->type = 0;
		}
	}
	free_input_matrix (input, i);
	return (list);
}
