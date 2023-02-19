
#include "minishell.h"

char	*get_expanded_var(char *cmd) 
{
	int	i;
	char	**aux_matrix;
	char	*var_value;
	char	*aux_str;

	char	*expand_cmd;
	char	*temp_str;
	char	*new_str;

	aux_matrix = ft_split(cmd, ' ');  
	i = 0;
	while (aux_matrix[i])
	{
		aux_str = ft_strtrim(aux_matrix[i], "\""); //ver aqui, pois talves precise voltar as aspas no
		if (aux_str[0] == '$')
		{
			var_value = ft_strtrim(aux_str, "$");
			free (aux_str);
			aux_str = getenv(var_value); //se for null? ver o que fazer
			if (var_value != NULL)
			{
				free(aux_matrix[i]);
				aux_matrix[i] = ft_strdup(aux_str);
				free (var_value);
			}
		}
		i++;
	}
	i = 0;
	while (aux_matrix[i])
	{
		if (i == 0)
			expand_cmd = ft_strdup(aux_matrix[i]);
		else
		{
			temp_str = ft_strjoin(expand_cmd, " ");
			new_str = ft_strjoin(expand_cmd, aux_matrix[i]);
			free (temp_str);
			free (expand_cmd);
			expand_cmd = new_str;
		}
		i++;
	}
	free_matrix(aux_matrix);
	return(expand_cmd);
}

void	env_var_checker(t_token *list, t_env *env_var)
{
	t_token	*aux;
	int		i;
	char	*expanded_cmd;

	aux = list;
	while (aux)
	{
		i = 0;
		while (aux->cmd && aux->cmd[i])
		{
			if (aux->cmd[i] == '$' && env_var->expand_var)
			{
				expanded_cmd = get_expanded_var(aux->cmd);
				free (aux->cmd);
				aux->cmd = ft_strdup(expanded_cmd); //strdup aqui tava dando leak pois to realocando em cima
				free(expanded_cmd);
				break ;
			}
			i++; //ele volta a olhar no msm cmd mas ja foi expandido e n encontra, o ideal seria ppara de olhar
		}
		aux = aux->next;
	}
}


//splitar / procurar o $ / expandir / concatenar /retornar
/*
char	*get_expanded_var(char *cmd) 
{
	int	i;
	char	**aux_matrix;
	char	*var_value;
	char	*expand_cmd;

	char	*temp_str;
	char	*new_str;

	aux_matrix = ft_split(cmd, ' ');  
	i = 0;
	while (aux_matrix[i])
	{
		aux_matrix[i] = ft_strtrim(aux_matrix[i], "\""); //ver aqui, pois talves precise voltar as aspas no
		if (aux_matrix[i][0] == '$')
		{
			aux_matrix[i] = ft_strtrim(aux_matrix[i], "$");
			var_value = getenv(aux_matrix[i]); //se for null? ver o que fazer
			if (var_value != NULL)
				aux_matrix[i] = ft_strdup(var_value);
		}
		i++;
	}
	i = 0;
	while (aux_matrix[i])
	{
		if (i == 0)
			expand_cmd = ft_strdup(aux_matrix[i]);
		else
		{
			temp_str = ft_strjoin(expand_cmd, " ");
			new_str = ft_strjoin(expand_cmd, aux_matrix[i]);
			free (temp_str);
			free (expand_cmd);
			expand_cmd = new_str;
		}
		i++;
	}
	free_matrix(aux_matrix);
	return(expand_cmd);
}
*/

// void	env_var_checker(t_token *list, t_env *env_var)
// {
// 	t_token	*aux;
// 	int		i;
// 	char	*expanded_cmd;

// 	aux = list;
// 	while (aux)
// 	{
// 		i = 0;
// 		while (aux->cmd && aux->cmd[i])
// 		{
// 			if (aux->cmd[i] == '$' && env_var->expand_var)
// 			{
// 				expanded_cmd = get_expanded_var(aux->cmd);
// 				free (aux->cmd);
// 				aux->cmd = expanded_cmd; //strdup aqui tava dando leak pois to realocando em cima
// 				free(expanded_cmd);
// 				break ;
// 			}
// 			i++; //ele volta a olhar no msm cmd mas ja foi expandido e n encontra, o ideal seria ppara de olhar
// 		}
// 		aux = aux->next;
// 	}
// }
