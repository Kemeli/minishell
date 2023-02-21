
#include "minishell.h"


//sempre expandir dentro de aspas duplas, nunca dentro de aspas simples
//problem: e se as aspas duplas estiverem em outro lugar, tipo la no começo do input, ai ferro

int	open_double_quotes(t_env_utils *env, char *input)
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
			while (input[i] && input[++i] != '\"')
			{
				if (input[i] == '$')
					env->expand_var = 1;
			}
			if (input[i] == '\"')
				open_quotes = 0;
		}
		i++;
	}
	return (open_quotes);
}
//aqui verifica se tem aspas duplas abertas apenas, para fins de retorno 
//de erro ja no começo da execução

int	open_single_quotes(t_env_utils *env, char *input)//bad name
{
	int	i;
	int	open_quotes;

	i = 0;
	env->expand_var = 1;
	if (!ft_strchr(input, '$'))
		env->expand_var = 0;
	open_quotes = 0;
		while (input[i])
	{
		if (input[i] == '\'')
		{
			open_quotes = 1;
			while (input[i] && input[++i] != '\'')
			{
				if (input[i] == '$')
					env->expand_var = 0;
			}
			if (input[i] == '\'')
				open_quotes = 0;
		}
		i++;
	}
	return (open_quotes);
} //problem: se as aspas simples estiverem dentro das aspas duplas, tem que expandir

int	opened_quotes(char *input, t_env_utils *env)
{
	if (open_single_quotes(env, input)) //se voltar zero é pq ficou fechada, se não é pq ficou aberta
		return (1);
	else if (open_double_quotes(env, input))
		return (1);
	return (0);
}
