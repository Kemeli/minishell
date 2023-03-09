/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaiane- < kdaiane-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 00:25:47 by kdaiane-          #+#    #+#             */
/*   Updated: 2023/03/09 12:34:29 by kdaiane-         ###   ########.fr       */
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
	char	**input;
	t_exec *exec = ft_calloc(sizeof(t_exec), 1);

	if (argv == NULL && argc == 0) // oque faxzer com isso?
		printf ("ARGS");
	// while (1)
	// {
	list = NULL;
	input = get_input(exec);
	if (input)
	{
		exec->envp_ms = envp_matrix(envp);
		list = lexer(input, list);
		print_list(list); //tirar
		sintax(list);
		free_matrix(input);
		execute(list, exec);
		free_list(list);
	}
	// }
	free (exec);
	rl_clear_history();
}
