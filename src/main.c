/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaiane- < kdaiane-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 00:25:47 by kdaiane-          #+#    #+#             */
/*   Updated: 2023/03/03 18:34:52 by kdaiane-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


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

	if (argv == NULL && argc == 0) // oque faxzer com isso?
		printf ("ARGS");

	list = NULL;
	input = get_input();
	list = lexer(input, list);
	print_list(list); //tirar
	sintax(list);
	free_matrix(input);
	execute(list, envp);
	free_list(list);// rodar com make runrl pra suprimir os leaks da readline()
	// free(env);
}

//status, o loop infinito ficava repitindo o minishell>
