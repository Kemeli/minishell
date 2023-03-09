/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatos-s <kmatos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 00:25:47 by kdaiane-          #+#    #+#             */
/*   Updated: 2023/03/14 01:52:39 by kdaiane-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_minishell	minishell;

void	print_list(t_token *list) //essa função vai sair
{
	t_token *aux;

	aux = list;
	while (aux)
	{
		printf("cmd: %s, type: %d\n", aux->cmd, aux->type);
		aux = aux->next;
	}
	printf("\n");
}

int	main(int argc, char **argv, char **envp)
{
	t_token	*list;
	t_list	*envp_list = NULL;
	char	**input;

	minishell.envp_list = envp_list;
	if (argv == NULL && argc == 0) // oque faxzer com isso?
		printf ("ARGS");
	set_listeners();
	envp_list = make_envp_list(envp, envp_list);
	while (1)
	{
		list = NULL;
		input = get_input(envp_list);
		if (input)
		{
			list = lexer(input, list);
			// print_list(list); //tirar
			if (list)
			{
				sintax(list);
				execute(list, envp_list, input);
				free_list(list);
			}
			free_matrix(input);
		}
	}
	free_minishell();
}

void	free_minishell(void)
{
	ft_lstclear(&minishell.envp_list, &free);
	free(minishell.envp_list);
	rl_clear_history();
}
