/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listeners.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaiane- < kdaiane-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 20:13:39 by kdaiane-          #+#    #+#             */
/*   Updated: 2023/03/30 20:13:40 by kdaiane-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	set_ctrl_c(void)
{
	struct sigaction	handler;

	handler.sa_flags = 0;
	handler.sa_handler = &handle_sigint;
	sigemptyset(&handler.sa_mask);
	if (sigaction(SIGINT, &handler, NULL))
		printf("Error installing SIGINT handler\n");
}

static void	set_ctrl_back_slash(void)
{
	struct sigaction	handler;

	handler.sa_flags = 0;
	handler.sa_handler = SIG_IGN;
	sigemptyset(&handler.sa_mask);
	if (sigaction(SIGQUIT, &handler, NULL))
		printf("Error installing SIGQUIT handler\n");
}

void	set_ctrl_c_heredoc(void)
{
	struct sigaction	handler;

	handler.sa_flags = 0;
	handler.sa_handler = &handle_heredoc_sigint;
	sigemptyset(&handler.sa_mask);
	if (sigaction(SIGINT, &handler, NULL))
		printf("Error installing SIGINT heredoc handler\n");
}

void	set_listeners(void)
{
	set_ctrl_back_slash();
	set_ctrl_c();
}
