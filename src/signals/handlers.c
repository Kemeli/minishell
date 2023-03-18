#include <minishell.h>

/*******************************************************************************
** SIGNAL HANDLERS
********************************************************************************
**
** These handlers are used by the sigaction function to handle user
** interactions like ctrl-c ctrl-\.
**
** In these handlers we SHOULD NOT use functions that are not listed in the
** async-signal-safe.
**
** https://man7.org/linux/man-pages/man7/signal-safety.7.html
**
** So for example, if you want to print something please make use of the write
** function instead of the printf function.
**
******************************************************************************/

/* SIGINT = Ctrl + C */
void	handle_sigint(int sig)
{
	int	stat;

	(void)sig;
	if (shell.current_pid != 0 && shell.state == S_EXEC)
	{
		kill(shell.current_pid, SIGINT);
		ft_putchar_fd('\n', STDERR_FILENO);
		return ;
	}
	if (shell.state == S_READ)
	{
		ft_putchar_fd('\n', STDERR_FILENO);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		return ;
	}
	if (shell.state == S_RDWR)
	{
		printf("shell.current_pid: %i\n", shell.current_pid);
		kill(shell.current_pid, SIGTERM);
		ft_putchar_fd('\n', STDERR_FILENO);
		// rl_replace_line("", 0);
		// rl_on_new_line();
		// rl_redisplay();
	}
}

/* SIGQUIT = Ctrl + \ */
void	handle_sigquit(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}
