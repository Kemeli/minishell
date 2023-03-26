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
	(void)sig;
	if (g_shell.current_pid != 0)
	{
		kill(g_shell.current_pid, SIGINT);
		ft_putchar_fd('\n', STDERR_FILENO);
		return ;
	}
	ft_putchar_fd('\n', STDERR_FILENO);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

/* SIGINT = Ctrl + C */
void	handle_heredoc_sigint(int sig)
{
	(void)sig;
	g_shell.stop_loop = !g_shell.stop_loop;
}

/* SIGQUIT = Ctrl + \ */
// void	handle_sigquit(int sig)
// {
// 	(void)sig;
//     rl_replace_line("", 0);
//     rl_on_new_line();
//     rl_redisplay();
// }


void    handle_sigquit(int sig)
{
    (void)sig;
    ft_putstr_fd("\r                                              \r", 1);
    rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();
}