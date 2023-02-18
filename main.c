/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaiane- < kdaiane-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 00:25:47 by kdaiane-          #+#    #+#             */
/*   Updated: 2023/02/18 20:37:23 by kdaiane-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_input()
{
	char	*input;
	char	*prompt;

	prompt = "minishell> ";
	input = readline(prompt);
	if (!input)
		exit (0);
	//print input -- tirar depois
	printf("%s\n", input);
	return (input);
}

int	main()
{
	t_token	*list;
	t_env	*env_var;
	char	*input;

	list = NULL;
	env_var = ft_calloc(sizeof(t_env), 1);
	input = get_input();
	if (opened_quotes(input, env_var))
	{
		ft_putstr_fd("error: opened quotes\n", 2);
		return (0);
	}
	list = lexer(input, list, env_var);
	free_list(list); //da free na lista // rodar com make runrl pra suprimir os leaks da readline()
}


//status, falta testar a env_var_checker, inclusive não está printando o cmd, deve ser coisa de free antes da hora
//God help me
//depois de fazer ela funcionar a prioridade vai ser refaotorar tudo