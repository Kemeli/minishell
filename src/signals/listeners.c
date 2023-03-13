#include <minishell.h>

void	set_ctrl_c(void)
{
	struct sigaction	sa;

	sa.sa_handler = &handle_sigint;
	sigaction(SIGINT, &sa, NULL);
}

void	set_ctrl_d(void)
{
	struct sigaction	sa;

	sa.sa_handler = &handle_sigquit;
	sigaction(SIGQUIT, &sa, NULL);
}

void	set_listeners(void)
{
	set_ctrl_d();
	set_ctrl_c();
}

