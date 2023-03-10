#include <minishell.h>


int	is_env_char(int c) //1º char só letra, arrumar depois
{
	if (ft_isalpha(c) || ft_isdigit(c) || c == '_' || c == '$')
	{
		return (1);
	}
	return (0);
}

// char	*getenv_check(char *input, t_env_utils *env, t_list *list_envp)
// {
// 	char	*sub;
// 	char	*trim;
// 	int		j;

// 	j = env->i;
// 	while (is_env_char(input[j]))
// 		j++;
// 	sub = ft_substr(input, env->i, j - env->i);
// 	trim = ft_strtrim(sub, "$"); 
// 	env->test = get_env(trim, list_envp);
// 	env->i = j;
// 	free (trim);
// 	if (!env->test)
// 		return (sub);
// 	free (sub); 
// 	return (env->test);
// }

char	*getenv_check(char *input, t_env_utils *env, t_list *list_envp)
{
	char	*sub;
	char	*trim;
	int		j;

	j = env->i;
	while (is_env_char(input[j]))
		j++;
	sub = ft_substr(input, env->i, j - env->i);
	trim = ft_strtrim(sub, "$"); 
	env->test = get_env(trim, list_envp);
	env->i = j;
	free (trim);
	if (!env->test)
		return (ft_strdup(""));
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

char *get_expanded_var(char *input, t_list *list_envp)
{
	char *new_input;
	int sp_quotes = 0;
	int	db_quotes = 0;
	t_env_utils *env;

	env = ft_calloc(sizeof (t_env_utils), 1);
	new_input = ft_calloc(ft_strlen(input), 1);
	while (input[env->i])
	{
		if (input[env->i] == '\"')
			db_quotes = !db_quotes;

		if (input[env->i] == '\'' && !db_quotes)
			sp_quotes = !sp_quotes;

		if (input[env->i] != '$' || sp_quotes)
		{
			env->ch_cpy = ft_substr(input, env->i, 1);
			env->ch_join = ft_strjoin(new_input, env->ch_cpy);
			free(env->ch_cpy);
			free(new_input);
			new_input = env->ch_join;
			env->i++;
		}
		else if (input[env->i] == '$' && !sp_quotes)
		{
			env->get_ret = getenv_check(input, env, list_envp);
			new_input = input_expander(new_input, env);
			free (env->get_ret);
		}
	}
	free(env);
	free (input);
	return (new_input); //rever
}
