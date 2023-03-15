

#include <minishell.h>

char	**envp_matrix(t_list *list_envp)
{
	int		i;
	int		size;
	char	**envp_mat;
	t_list	*aux;

	aux = list_envp;
	size = ft_lstsize(aux);
	envp_mat = ft_calloc(sizeof (char *), size + 1);
	i = 0;
	while (i < size && aux)
	{
		envp_mat[i] = ft_strdup(aux->content);
		aux = aux->next;
		i++;
	}	
	envp_mat[i] = NULL;
	return (envp_mat);
}

char	*get_env(char *var, t_list *list_envp)
{
	char	*join;
	char	*expanded;
	char	*temp;
	int		check;
	t_list	*aux;

	aux = list_envp;
	expanded = NULL;
	join = ft_strjoin(var, "=");
	while (aux)
	{
		check = ft_strncmp(join, aux->content, ft_strlen(join));
		if (!check)
		{
			temp = ft_strdup (aux->content);
			expanded = ft_substr (temp, ft_strlen(var) + 1, ft_strlen(temp));
			free (temp);
			return (expanded);
		}
		aux = aux->next;
	}
	free (join);
	return (expanded); //rever
}

t_list	*make_envp_list(char **envp, t_list *envp_list)
{
	int	i;
	t_list	*new;

	i = 0;
	while (envp[i])
	{
		new = ft_lstnew(ft_strdup(envp[i]));
		ft_lstadd_back (&envp_list, new);
		i++;
	}
	return (envp_list);
}

void	set_pwd(t_list *envp_list)
{
	t_list	*aux;
	char	*temp;

	aux = envp_list;
	while (aux && !ft_strncmp(aux->content, "PWD", 3))
		aux = aux->next;

	if (ft_strncmp(aux->content, "PWD", 3))
	{
		free (aux->content);
		temp = getcwd(NULL, 0);
		getcwd(temp, sizeof(temp));
		aux->content = ft_strjoin ("PWD=", temp);
		free (temp);
	}
}
