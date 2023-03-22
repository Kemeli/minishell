
#include <minishell.h>

int	ft_unset(char **cmd, t_list *envp_list)
{
	t_list	*aux;
	int		check;
	int		i;

	if (!check_valid_envar(cmd, "unset: `", "': not a valid identifier", 0))
		return (1);
	i = 0;
	while (cmd[i])
	{
		aux = envp_list;
		while (aux)
		{
			check = ft_strncmp(cmd[i], aux->content, ft_strlen(cmd[i]));
			if (check == 0)
			{
				free (aux->content);
				aux->content = ft_strdup("");
				break ;
			}
			aux = aux->next;
		}
		i++;
	}
	return (1);
}
