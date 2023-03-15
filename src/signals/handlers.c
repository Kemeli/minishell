#include <minishell.h>

void	handle_sigint(int sig)
{
	(void)sig;

	if (shell.current_pid != 0)
	{
		kill(shell.current_pid, SIGINT);
		ft_putchar_fd('\n', STDERR_FILENO);
		return ;
	}
	ft_putchar_fd('\n', STDERR_FILENO);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	handle_sigquit(int sig)
{
	(void)sig;

	free_shell();
	if (shell.current_pid != 0)
		ft_putchar_fd('\n', STDERR_FILENO);
}
