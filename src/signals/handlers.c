#include <minishell.h>

void	handle_sigint(int sig)
{
	(void)sig;

	if (minishell.current_command && !ft_strncmp(minishell.current_command, "<<", 2))
	{
		printf("\n");
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
		return ;
	}
	ft_putchar_fd('\n', STDERR_FILENO);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	handle_sigquit(int sig)
{
	free_minishell();
	exit(sig);
}
