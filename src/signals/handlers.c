#include <minishell.h>

void	handle_sigint(int sig)
{
	(void)sig;

	if (minishell.current_pid != 0)
	{
		kill(minishell.current_pid, SIGINT);
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
	if (minishell.current_pid != 0)
		write(2, "\n", 1);
}
