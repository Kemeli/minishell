
#include "minishell.h"

//precisa lidar com o caso de ser invalid
//precisa lidar com o caso de estar entre aspas e cheio de espaços

char	*get_split(char *input)
{
	char **matrix = ft_split(input, ' ');
	char *trim = ft_strtrim(matrix[0], "$\"");
	free_matrix(matrix);
	return (trim);
}

char	*getenv_check(char *input, t_env_utils *env)
{
	env->env_var = get_split(&input[env->i]);
	env->var_size = ft_strlen(env->env_var);
	env->test = getenv(env->env_var);
	free(env->env_var);
	env->i++;
	return (env->test);
}

char	*input_expansor(char *new_input, t_env_utils *env)
{
	env->i += env->var_size;
	env->temp = ft_strjoin(new_input, env->test);
	env->test = NULL;
	free (new_input);
	new_input = ft_strdup(env->temp);
	free (env->temp);
	return (new_input);
}

//PROBLEM -- não está expandindo com caractere grudado ex: $PATH<  deveria expandir normal
char *get_expanded_var(char *input, t_env_utils *env)
{
	char	*new_input;

	new_input = ft_calloc(ft_strlen(input), 1);
	if (!env->expand_var)
		return input;
	while (input[env->i])
	{
		while (input[env->i] && input[env->i] != '$')
		{
			env->ch_cpy = ft_substr(input, env->i, 1); //joinfree talvez fosse melhor
			env->ch_join = ft_strjoin(new_input, env->ch_cpy);
			free(env->ch_cpy);
			free(new_input);
			new_input = env->ch_join;
			env->i++;
		}
		if (input[env->i] == '$')
			env->get_ret = getenv_check(input, env);
		if (env->get_ret) //n foi inicializado pra null mas se n tiver $ n é pra chegar até aqui
			new_input = input_expansor(new_input, env);
	}
	free (env);
	return (new_input);
}
