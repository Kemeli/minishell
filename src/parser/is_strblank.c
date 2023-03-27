#include <minishell.h>

int	is_strblank(char *str)
{
	while (*str && *str == ' ')
		str++;
	if (!*str)
		return (1);
	return (0);
}
