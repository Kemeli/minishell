#include <minishell.h>

static char	*getenv_check(char *input, t_envar *env, t_list *list_envp)
{
	char	*sub;
	char	*trim;
	int		j;

	j = env->i;
	while (is_env_char(input[j]))
		j++;
	sub = ft_substr(input, env->i, j - env->i);
	trim = ft_strtrim(sub, "$");
	env->i = j;
	if (!ft_strncmp(trim, "", 2))
	{
		free (trim);
		return (sub);
	}
	env->test = get_env(trim, list_envp);
	free (trim);
	if (!env->test || !ft_strncmp(env->test, "", 2))
		return (sub);
	free (sub);
	return (env->test);
}

static char	*input_expander(char *new_input, t_envar *env)
{
	env->temp = ft_strjoin(new_input, env->get_ret);
	env->test = NULL;
	free (new_input);
	new_input = ft_strdup(env->temp);
	free (env->temp);
	if (!env->i)
		env->i++;
	return (new_input);
}

static char	*cpy_bytes(t_envar *env, char *new_input, char *input)
{
	env->ch_cpy = ft_substr(input, env->i, 1);
	env->ch_join = ft_strjoin(new_input, env->ch_cpy);
	free(env->ch_cpy);
	free(new_input);
	new_input = env->ch_join;
	env->i++;
	return (new_input);
}

char	*expander(char *input, t_envar *env, char *new_input, t_list *envp)
{
	if (input[++env->i] && input[env->i] == '?')
	{
		env->status = ft_itoa (g_shell.exit_status);
		env->stt_join = ft_strjoin (new_input, env->status);
		free(new_input);
		new_input = ft_strdup(env->stt_join);
		env->i += 1;
	}
	else
	{
		env->i--;
		env->get_ret = getenv_check(input, env, envp);
		new_input = input_expander(new_input, env);
		free (env->get_ret);
	}
	return (new_input);
}

char	*get_expanded_var(char *input, t_list *envp, int hd)
{
	t_envar	*env;
	char	*new_input;

	if (input && !ft_strchr(input, '$'))
		return (input);
	env = ft_calloc(sizeof (t_envar), 1);
	new_input = ft_calloc(ft_strlen(input), 1);
	while (input[env->i])
	{
		if (input[env->i] == '\"')
			env->db_quotes = !env->db_quotes;
		if (input[env->i] == '\'' && !env->db_quotes && !hd)
			env->sp_quotes = !env->sp_quotes;
		if (input[env->i] != '$' || env->sp_quotes)
			new_input = cpy_bytes(env, new_input, input); //leak?
		else if (input[env->i] == '$' && !env->sp_quotes)
			new_input = expander (input, env, new_input, envp);
	}
	free(env);
	free (input);
	return (new_input); //rever
}
