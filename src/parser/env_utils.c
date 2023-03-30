/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaiane- < kdaiane-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 20:12:31 by kdaiane-          #+#    #+#             */
/*   Updated: 2023/03/30 20:12:32 by kdaiane-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*get_env(char *var, t_list *list_envp)
{
	char	*join;
	char	*expanded;
	char	*temp;
	int		check;
	t_list	*aux;

	aux = list_envp;
	expanded = NULL;
	join = ft_strjoin(var, "=");
	while (aux)
	{
		check = ft_strncmp(join, aux->content, ft_strlen(join));
		if (!check)
		{
			temp = ft_strdup (aux->content);
			expanded = ft_substr (temp, ft_strlen(var) + 1, ft_strlen(temp));
			free (join);
			free (temp);
			return (expanded);
		}
		aux = aux->next;
	}
	free (join);
	return (expanded);
}

t_list	*make_envp_list(char **envp, t_list *envp_list)
{
	int		i;
	t_list	*new;

	i = 0;
	while (envp[i])
	{
		new = ft_lstnew(ft_strdup(envp[i]));
		ft_lstadd_back (&envp_list, new);
		i++;
	}
	return (envp_list);
}

int	is_env_char(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c) || c == '_' || c == '$')
	{
		return (1);
	}
	return (0);
}
