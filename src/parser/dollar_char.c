/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaiane- < kdaiane-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 20:12:25 by kdaiane-          #+#    #+#             */
/*   Updated: 2023/03/30 20:12:26 by kdaiane-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	ignore_invalid_input(char *input, int i)
{
	i++;
	if (input[i] && (ft_isalpha(input[i]) || !ft_strncmp(&input[i], "_", 2)))
	{
		i++;
		while (input[i] && input[i] != '=' && (ft_isalpha(input[i])
				|| ft_isdigit(input[i]) || input[i] == '_'))
			i++;
	}
	else if (input[i] && ft_isdigit(input[i]))
		i++;
	return (i);
}

static char	*cpy_bytes(char *temp, char *ret, char *new_input, int i)
{
	char	*sub;

	if (!ret)
		ret = ft_calloc (sizeof (char *), 1);
	sub = ft_substr (new_input, i, 1);
	temp = ft_strjoin (ret, sub);
	free_null (&ret);
	ret = ft_strdup (temp);
	free_null (&temp);
	free_null (&sub);
	return (ret);
}

static char	*single_dollar(t_dollar *dollar, char *input, int i)
{
	i++;
	dollar->key = 0;
	if (!input[i] || input[i] == ' '
		|| input[i] == '\"' || input[i] == '$')
	{
		if (!dollar->ret)
			dollar->ret = ft_calloc (sizeof(char *), 1);
		dollar->temp = ft_strjoin(dollar->ret, "$");
		free_null (&dollar->ret);
		dollar->ret = ft_strdup (dollar->temp);
		free_null (&dollar->temp);
		dollar->key = 1;
	}
	return (dollar->ret);
}

static char	*validate_dollar(char *input, t_dollar *dollar, int i)
{
	int		sp_quotes;

	sp_quotes = 0;
	while (input && input[i])
	{
		while (input[i] && (input[i] != '$'))
		{
			if (input[i] == '\'')
				sp_quotes = !sp_quotes;
			dollar->ret = cpy_bytes(dollar->temp, dollar->ret, input, i);
			i++;
		}
		if (input[i] && input[i] == '$')
			dollar->ret = single_dollar (dollar, input, i);
		if (input[i] && input[i] == '$' && !sp_quotes && !dollar->key)
			i = ignore_invalid_input(input, i);
		if (input[i] && input[i] == '$' && sp_quotes && !dollar->key)
			dollar->ret = cpy_bytes(dollar->temp, dollar->ret, input, i);
		if (input[i] && input[i] != '=')
			i++;
	}
	return (dollar->ret);
}

char	*handle_dollar(char *input)
{
	char		*ret;
	char		*new_input;
	int			i;
	t_dollar	*dollar;

	i = 0;
	new_input = ft_strdup (input);
	free_null (&input);
	if (!ft_strchr (new_input, '$'))
		return (new_input);
	dollar = ft_calloc(sizeof (t_dollar), 1);
	ret = validate_dollar(new_input, dollar, i);
	free_null (&new_input);
	free (dollar);
	return (ret);
}
