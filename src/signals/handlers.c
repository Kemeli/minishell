/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaiane- < kdaiane-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 20:13:25 by kdaiane-          #+#    #+#             */
/*   Updated: 2023/03/30 20:13:27 by kdaiane-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	handle_sigint(int sig)
{
	(void)sig;
	g_shell.exit_status = 130;
	if (g_shell.current_pid != 0)
	{
		kill(g_shell.current_pid, SIGINT);
		ft_putchar_fd('\n', STDOUT_FILENO);
		return ;
	}
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	handle_heredoc_sigint(int sig)
{
	(void)sig;
	g_shell.stop_loop = !g_shell.stop_loop;
}
