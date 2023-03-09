#include <minishell.h>

void	handle_sigint(int sig)
{
	free_minishell();
	exit(sig);
}
