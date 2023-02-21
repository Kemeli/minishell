
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

//char	*expand_input(char *input)

char	*make_char(char c)
{
	char character[] = {c, '\0'};
	char *ret = character;
	return (ret);
}

//new_input sempre tem algo dentro dele
//$PATH $USER expande o user e some com o path
//$PATH expande o path com caracteres a mais no começo
char *get_expanded_var(char *input, t_env_utils *env)
{
	int		i = 0;
	char	*env_var;
	// char	test[1024];
	char	*test;
	char	*new_input = ft_calloc(ft_strlen(input), 1);
	char	*temp;
	char	*temp2;
	char	*temp3;

	if (!env->expand_var)
		return input;

	while (input[i])
	{
		// ft_bzero (test, 1024);
		while (input[i] && input[i] != '$')
		{
			temp3 = ft_substr(input, i, 1); //joinfree talvez fosse melhor
			temp2 = ft_strjoin(new_input, temp3);
			free(temp3);
			free(new_input);
			new_input = temp2;
			i++;
		}
		if (input[i] == '$')
		{
			env_var = get_split(&input[i]);
			i += ft_strlen(env_var) + 1;
			test = getenv(env_var);
			free(env_var);
		}
		if (test)
		{
			temp = ft_strjoin(new_input, test);
			test = NULL;
			free (new_input);
			new_input = ft_strdup(temp);
			free (temp);
		}
	}
	return (new_input);
}
