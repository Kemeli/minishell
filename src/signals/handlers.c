#include <minishell.h>

void	handle_sigint(int sig)
{
	printf("should cancel current line and create a new one: %i\n", sig);
}

void	handle_sigquit(int sig)
{
	free_minishell();
	exit(sig);
}
