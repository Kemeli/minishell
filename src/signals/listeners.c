#include <minishell.h>

static void	set_sigint_listener(void)
{
	signal(SIGINT, handle_sigint);
}

void	set_listeners(void)
{
	set_sigint_listener();
}
