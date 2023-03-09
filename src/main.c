/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaiane- < kdaiane-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 00:25:47 by kdaiane-          #+#    #+#             */
/*   Updated: 2023/03/10 00:45:09 by kdaiane-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>


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

	if (argv == NULL && argc == 0) // oque faxzer com isso?
		printf ("ARGS");
	envp_list = make_envp_list(envp, envp_list);
	while (1)
	{
		list = NULL;
		input = get_input(envp_list);
		if (input)
		{
			list = lexer(input, list);
			print_list(list); //tirar
			sintax(list);
			free_matrix(input);
			execute(list, envp_list);
			free_list(list);
		}
	}
	ft_lstclear(&envp_list, &free);
	free(envp_list);
	rl_clear_history();
}
