
#include "minishell.h"


//splitar / procurar o $ / expandir / concatenar /retornar
char	*get_expanded_var(char *cmd) //  "haaa $USER $PATH" //teria que splitar, pegar as var, expandir e depois concatenar nvamente
{
	int	i;
	char	*expand_cmd;
	char	**temp;
	char	*var_value;

	temp = ft_split(cmd, ' ');
	i = 0;
	while (temp[i])
	{
		temp[i] = ft_strtrim(temp[i], "\"");
		if (temp[i][0] == '$')
		{
			temp[i] = ft_strtrim(temp[i], "$");
			var_value = getenv(temp[i]); //se for null? ver o que fazer
			if (var_value != NULL)
				temp[i] = ft_strdup(var_value);
		}
		i++;
	}
	i = 0;
	while (temp[i])
	{
		if (i == 0)
			expand_cmd = ft_strdup(temp[i]);
		else
		{
			expand_cmd = ft_strjoin(expand_cmd, temp[i]);
			expand_cmd = ft_strjoin(expand_cmd, " ");
		}
		i++;
	}
	return(expand_cmd);
}

// char	*middle_trim(char *cmd)
// {
// 	int		i;
// 	int		k;
// 	int		j;
// 	char	*dollar_var;
// 	char	*var_content;
// 	char	*expand_cmd;

// 	i = 0;
// 	j = 0;
// 	k = 0;
// 	var_content = ft_calloc(ft_strlen(cmd), 1);
// 	expand_cmd = ft_calloc(ft_strlen(cmd), 1);
// 	dollar_var = ft_calloc(ft_strlen(cmd), 1);
// 	while (cmd[i])
// 	{
// 		while(cmd[i] != '$')
// 			expand_cmd[j] = cmd[i];
// 		if (cmd[i] == '$')
// 		{
// 			while (cmd[++i] && cmd[i] != ' ')
// 				dollar_var[k++] = cmd[i];
// 			var_content = getenv(dollar_var); //colocar proteção de erro pois se não for valido deve retornar 0 e ai vai dar ruim
// 			j = ft_strlcat(expand_cmd, var_content, ft_strlen(var_content));
// 			// j += ft_strlen(expand_cmd); // ou j = strlcat, que retorna 
// 		}
// 		i++;
// 		j++;
// 	}
// 	// free(var_content);
// 	return(expand_cmd);
// }

//tirar aspas para expandir? acho q sim né
//falta expandir direito esse role aqui
void	env_var_checker(t_token *list, t_env *env_var)
{
	t_token	*aux;
	int		i;
	char	*expanded_cmd;

	aux = list;
	while (aux)
	{
		i = 0;
		while (aux->cmd[i])
		{
			if (aux->cmd[i] == '$' && env_var->expand_var)
			{
				expanded_cmd = get_expanded_var(aux->cmd);
				aux->cmd = ft_strdup(expanded_cmd);
			}
			i++;
		}
		aux = aux->next;
	}
}
