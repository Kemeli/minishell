/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sintax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaiane- < kdaiane-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 20:13:08 by kdaiane-          #+#    #+#             */
/*   Updated: 2023/03/30 20:32:35 by kdaiane-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	ft_putstr_fd ("minishell: syntax error near token `", 2);
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
