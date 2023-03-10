#include <minishell.h>

void	set_listeners(void)
{
	signal(SIGQUIT, handle_sigquit);
	signal(SIGINT, handle_sigint);
}
