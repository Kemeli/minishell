/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaiane- < kdaiane-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 20:10:45 by kdaiane-          #+#    #+#             */
/*   Updated: 2023/03/30 20:10:46 by kdaiane-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_env(t_list *envp_list, char **cmd)
{
	char	**matrix;
	int		i;

	i = 0;
	if (cmd && cmd[1])
	{
		status ("minishell: env: ‘", cmd[1], "’: invalid parameter", 127);
		return (1);
	}
	matrix = envp_matrix(envp_list);
	while (matrix[i])
	{
		if (matrix[i][0] == '\0')
		{
			i++;
			continue ;
		}
		ft_putendl_fd(matrix[i], 1);
		i++;
	}
	free_matrix (matrix);
	return (1);
}
