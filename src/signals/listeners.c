#include <minishell.h>

void	set_ctrl_c(void)
{
	struct sigaction	handler;

	handler.sa_handler = &handle_sigint;
	if (sigaction(SIGINT, &handler, NULL))
		printf("Error installing SIGINT handler\n");
}

void	set_ctrl_d(void)
{
	struct sigaction	handler;

	handler.sa_handler = &handle_sigquit;
	if (sigaction(SIGQUIT, &handler, NULL))
		printf("Error installing SIGQUIT handler\n");
}

void	set_listeners(void)
{
	set_ctrl_d();
	set_ctrl_c();
}

