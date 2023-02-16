/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaiane- < kdaiane-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 00:25:47 by kdaiane-          #+#    #+#             */
/*   Updated: 2023/02/16 15:37:25 by kdaiane-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_input()
{
	char	*input;
	char	*prompt;

	prompt = "minishell> ";
	input = readline(prompt);

	//print input -- tirar depois
	printf("%s\n", input);
	return (input);
}

void	free_list(t_token *list)
{
	t_token	*aux;

	while(list != NULL)
	{
		aux = list;
		list = list->next;
		free(aux);
	}
	free(list);
}

int main()
{
	t_token *list;
	char	*input;

	list = NULL;
	input = get_input(); //recebe o input como string
	list = lexer(input, list); //recebe a lista duplamente encadeada
	free_list(list); //da free na lista // rodar com make runrl pra suprimir os leaks da readline()
}

//n está tudo na norma ainda 😓