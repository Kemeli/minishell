
#include "minishell.h"

//precisa lidar com o caso de ser invalid
//precisa lidar com o caso de estar entre aspas e cheio de espaços

//está colocando caracteres invalidos dentro da saída em alguns casos específicos
//esta printando aspas quando mandado apenas uma var, e não deveria
// char *get_expanded_var(char *input, t_env *env_var)
// {
// 	int i;
// 	int j;
// 	char *expanded_input;
// 	t_utils *utils;

// 	if (!env_var->expand_var) 
// 		return input;

// 	i = 0;
// 	j = 0;
// 	expanded_input = ft_calloc(strlen(input) + 1, sizeof(char));
// 	utils = ft_calloc(sizeof(t_utils), 1);
// 	while (input[i]) 
// 	{
// 		if (input[i] == '$')
// 		{
// 			utils->teste4 = ft_split(&input[i], ' ');
// 			utils->teste2 = ft_strtrim(utils->teste4[0], "$\"");
// 			utils->teste3 = getenv(utils->teste2);
// 			if (utils->teste3 != NULL)
// 			{
// 				utils->teste = ft_strjoin(expanded_input, utils->teste3);
// 				free (expanded_input);
// 				expanded_input = ft_strjoin(expanded_input, utils->teste);
// 				free (utils->teste);
// 				i += ft_strlen(utils->teste2) + 1; //1 do $ e 1 do i++
// 				j = strlen(expanded_input);
// 			}
// 			free_matrix(utils->teste4);
// 			free(utils->teste2);
// 		}
// 		expanded_input[j] = input[i];
// 		j++;
// 		i++;
// 	}
// 	expanded_input[j] = '\0';

// 	free(utils);

// 	return expanded_input;
// }



char	*get_split(char *input)
{
	char **matrix = ft_split(input, ' ');
	char *trim = ft_strtrim(matrix[0], "$");
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
char *get_expanded_var(char *input, t_env *env)
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
		while (input[i] != '$')
		{
			temp3 = ft_substr(input, i, 1);
			temp2 = ft_strjoin(new_input, temp3); //joinfree
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
