/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaiane- < kdaiane-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 20:13:03 by kdaiane-          #+#    #+#             */
/*   Updated: 2023/03/30 20:13:03 by kdaiane-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*cpy_character(char *str, char *new, int i)
{
	char	*chr;
	char	*temp;

	if (str[i])
	{
		chr = ft_substr(str, i, 1);
		temp = ft_strjoin(new, chr);
		free (chr);
		free_null(&new);
		new = ft_strdup(temp);
		free (temp);
	}
	return (new);
}

static int	ignore_adjacent_quotes(char *str, int i, t_cut_quotes *cut)
{
	if (str[i] == '\"' && !cut->sp_quotes)
	{
		cut->db_quotes = !cut->db_quotes;
		i++;
		while (str[i] == '\"')
		{
			cut->db_quotes = !cut->db_quotes;
			i++;
		}
	}
	if (str[i] == '\'' && !cut->db_quotes)
	{
		cut->sp_quotes = !cut->sp_quotes;
		i++;
		while (str[i] == '\'')
		{
			cut->sp_quotes = !cut->sp_quotes;
			i++;
		}
	}
	return (i);
}

char	*cut_quotes(char *str)
{
	t_cut_quotes	*cut;
	char			*new;
	int				i;

	i = 0;
	cut = ft_calloc (sizeof (t_cut_quotes), 1);
	new = ft_calloc (sizeof(char *), 1);
	while (str[i])
	{
		i = ignore_adjacent_quotes(str, i, cut);
		new = cpy_character(str, new, i);
		if (str[i])
			i++;
	}
	free (str);
	free (cut);
	return (new);
}
