
#include <minishell.h>

int	open_double_quotes(char *input)
{
	int	i;
	int	open_quotes;

	i = 0;
	open_quotes = 0;
	while (input[i])
	{
		if (input[i] == '\"')
		{
			open_quotes = 1;
			while (input[i] && input[++i] != '\"');
			if (input[i] == '\"')
				open_quotes = 0;
		}
		i++;
	}
	return (open_quotes);
}

int	open_single_quotes(char *input)
{
	int	i;
	int	open_quotes;

	i = 0;
	open_quotes = 0;
	while (input[i])
	{
		if (input[i] == '\'')
		{
			open_quotes = 1;
			while (input[i] && input[++i] != '\'');
			if (input[i] == '\'')
				open_quotes = 0;
		}
		i++;
	}
	return (open_quotes);
}

int	opened_quotes(char *input)
{
	if (open_single_quotes(input)) //se voltar zero é pq ficou fechada, se não é pq ficou aberta
		return (1);
	else if (open_double_quotes(input))
		return (1);
	return (0);
}
