
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
	if (!env->test)
		return (&input[env->i]);
	env->i++; //checar a necessidade
	return (env->test);
}

char	*input_expander(char *new_input, t_env_utils *env)
{
	env->i += env->var_size;
	env->temp = ft_strjoin(new_input, env->get_ret);
	env->test = NULL;
	free (new_input);
	new_input = ft_strdup(env->temp);
	free (env->temp);
	if(!env->i) //aqui é por causa do $ e do $NADA
		env->i++;
	return (new_input);
}

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
		{
			env->get_ret = getenv_check(input, env);
			if (!env->test) //aqui é por causa do $ e do $NADA
				env->i++;
			new_input = input_expander(new_input, env);
			env->get_ret = NULL;
		}	
	}
	free (env);
	return (new_input);
}

//"$PATH" quando termina de copiar ele volta a entrar na linha 57 pois afinal ele ainda está com o valor