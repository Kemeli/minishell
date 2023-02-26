
#include "../minishell.h"

int	is_env_char(int c) //1º char só letra, arrumar depois
{
	if (ft_isalpha(c) || ft_isdigit(c) || c == '_' || c == '$')
	{
		return (1);
	}
	return (0);
}

char	*getenv_check(char *input, t_env_utils *env)
{
	char	*sub;
	char	*trim;
	int		j;
	
	j = env->i;
	while (is_env_char(input[j]))
		j++;
	sub = ft_substr(input, env->i, j - env->i);
	trim = ft_strtrim(sub, "$");
	env->test = getenv(trim);
	env->i = j;
	free (trim);
	if (!env->test)
		return (sub); //isso aqui esta causando leak, consegui dar free no retorno, como resolver?
	free (sub); 
	return (env->test);

}

char	*input_expander(char *new_input, t_env_utils *env)
{
	env->temp = ft_strjoin(new_input, env->get_ret);
	env->test = NULL;
	free (new_input);
	new_input = ft_strdup(env->temp);
	free (env->temp);
	if(!env->i)
		env->i++;
	return (new_input);
}

char *get_expanded_var(char *input, t_env_utils *env)
{
	char *new_input;
	int in_quotes = 0;

	new_input = ft_calloc(ft_strlen(input), 1);

	while (input[env->i])
	{
		if (input[env->i] == '\'')
			in_quotes = !in_quotes;

		if (input[env->i] != '$' || in_quotes)
		{
			env->ch_cpy = ft_substr(input, env->i, 1);
			env->ch_join = ft_strjoin(new_input, env->ch_cpy);
			free(env->ch_cpy);
			free(new_input);
			new_input = env->ch_join;
			env->i++;
		}

		else if (input[env->i] == '$' && !in_quotes)
		{
			env->get_ret = getenv_check(input, env);
			new_input = input_expander(new_input, env);
			env->get_ret = NULL; //precisa disso?
		}
	}
	free(env);
	return (new_input);
}
