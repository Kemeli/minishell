/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaiane- < kdaiane-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 00:25:47 by kdaiane-          #+#    #+#             */
/*   Updated: 2023/02/20 14:35:38 by kdaiane-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


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

int	main()
{
	t_token	*list;
	t_env	*env_var;
	char	**input;

	list = NULL;
	env_var = ft_calloc(sizeof(t_env), 1);
	input = get_input(env_var);

	
	list = lexer(input, list);
	print_list(list); //tirar
	free_list(list);// rodar com make runrl pra suprimir os leaks da readline()
	free(env_var);
	free_matrix(input); //talvez esse free de problema na lista, talvez colocar ele no final
}
