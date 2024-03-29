/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaiane- < kdaiane-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 20:11:52 by kdaiane-          #+#    #+#             */
/*   Updated: 2023/03/30 20:11:53 by kdaiane-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	**alloc_eof(t_token *aux)
{
	t_token	*node;
	int		count;
	char	**here_args;

	node = aux;
	count = 0;
	while (node)
	{
		if (node->type == HERE_ARG)
			count++;
		node = node->next;
	}
	here_args = ft_calloc(sizeof(char *), count + 1);
	return (here_args);
}

char	**eof_matrix(t_token **aux)
{
	char	**eof_matrix;
	int		i;

	i = 0;
	eof_matrix = alloc_eof(*aux);
	if ((*aux)->type == HEREDOC)
		(*aux) = (*aux)->next;
	while (*aux && ((*aux)->type == HERE_ARG || (*aux)->type == HEREDOC))
	{
		if ((*aux)->type == HERE_ARG)
		{
			eof_matrix[i] = ft_strdup((*aux)->cmd);
			i++;
		}
		if ((*aux)->next && ((*aux)->next->type == HERE_ARG
				|| (*aux)->next->type == HEREDOC))
			(*aux) = (*aux)->next;
		else
			break ;
	}
	eof_matrix[i] = NULL;
	return (eof_matrix);
}

char	**heredoc_matrix(char *input)
{
	int		i;
	int		j;
	char	**temp;
	char	**here_matrix;
	char	*dollar;

	i = 0;
	j = -1;
	temp = ft_split(input, '\n');
	while (temp[i])
		i++;
	here_matrix = ft_calloc (sizeof(char *), i + 1);
	i = 0;
	while (temp[i])
	{
		dollar = handle_dollar(temp[i]);
		if (dollar)
			here_matrix[++j] = ft_strdup(dollar);
		free (dollar);
		i++;
	}
	j++;
	here_matrix[i] = NULL;
	free (temp);
	return (here_matrix);
}

char	*join_heredoc_input(char *input, char *read)
{
	char	*temp;

	temp = ft_strjoin(input, read);
	free (input);
	input = ft_strjoin(temp, "\n");
	free(temp);
	return (input);
}
