/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaiane- < kdaiane-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 00:25:47 by kdaiane-          #+#    #+#             */
/*   Updated: 2023/02/28 17:58:16 by kdaiane-         ###   ########.fr       */
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
}

int	main(int argc, char **argv, char **envp)
{
	t_token	*list;
	t_env_utils	*env;
	// t_exec *exec;
	char	**input;


	if (argv == NULL && argc == 0)
	{
		printf ("ARGS");
	}

	list = NULL;
	env = ft_calloc(sizeof(t_env_utils), 1);
	input = get_input(env);
	list = lexer(input, list);
	print_list(list); //tirar
	sintax(list);
	//daqui pra baixo talvez fazer um loop
	// redirector(list);
	// cmd_handler(list, envp);
	execute(list, envp);
	free_list(list);// rodar com make runrl pra suprimir os leaks da readline()
	free(env);
	free_matrix(input); //talvez esse free de problema na lista, talvez colocar ele no final
}

//status, o loop infinito ficava repitindo o minishell>
