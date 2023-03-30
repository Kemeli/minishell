/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaiane- < kdaiane-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 20:10:39 by kdaiane-          #+#    #+#             */
/*   Updated: 2023/03/30 20:10:40 by kdaiane-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_echo(char **cmd)
{
	int	i;
	int	new_line;

	i = 1;
	new_line = 1;
	if (cmd[i])
	{
		if (!ft_strncmp(cmd[i], "-n", 3))
		{
			new_line = !new_line;
			i++;
		}
		while (cmd[i])
		{
			ft_putstr_fd (cmd[i], STDOUT_FILENO);
			i++;
			if (cmd[i])
				ft_putstr_fd (" ", STDOUT_FILENO);
		}
	}
	if (new_line)
		ft_putstr_fd("\n", STDOUT_FILENO);
	g_shell.exit_status = 0;
	return (1);
}
