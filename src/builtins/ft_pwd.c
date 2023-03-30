/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaiane- < kdaiane-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 20:11:01 by kdaiane-          #+#    #+#             */
/*   Updated: 2023/03/30 20:11:03 by kdaiane-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_pwd(void)
{
	char	*pwd;

	pwd = NULL;
	pwd = getcwd(pwd, BUFFER);
	if (pwd == NULL)
	{
		g_shell.exit_status = 42;
		free (pwd);
		return (0);
	}
	printf ("%s\n", pwd);
	free (pwd);
	return (1);
}
