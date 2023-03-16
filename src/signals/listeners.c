#include <minishell.h>

/*****************************************************************************************
** SIGNAL LISTENERS
******************************************************************************************
**
** These listeners are used to attach some function to some signal.
**
** Please make sure to always use `sigaction` for the attachment of some handler
** function to some specific signal. The `signal` function works, but has portability
** issues across unix systems. https://man7.org/linux/man-pages/man7/signal.7.html
**
*****************************************************************************************/

void	set_ctrl_c(void)
{
	struct sigaction	handler;

	handler.sa_flags = 0;
	handler.sa_handler = &handle_sigint;
	sigemptyset(&handler.sa_mask);
	if (sigaction(SIGINT, &handler, NULL))
		printf("Error installing SIGINT handler\n");
}

void	set_ctrl_d(void)
{
	struct sigaction	handler;

	handler.sa_flags = 0;
	handler.sa_handler = &handle_sigquit;
	sigemptyset(&handler.sa_mask);
	if (sigaction(SIGQUIT, &handler, NULL))
		printf("Error installing SIGQUIT handler\n");
}

void	set_listeners(void)
{
	set_ctrl_d();
	set_ctrl_c();
}

