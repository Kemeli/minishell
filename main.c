/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaiane- < kdaiane-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 00:25:47 by kdaiane-          #+#    #+#             */
/*   Updated: 2023/02/18 21:10:28 by kdaiane-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_input()
{
	char	*input;
	char	*prompt;

	prompt = "minishell> ";
	input = readline(prompt); ///CRASH se for um enter, não é null, precisa tratar, retorna empty str 
	// if (input == ft_strdup("")) //isso aqui n funcionou
	// 	exit (0);

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
	free_list(list);// rodar com make runrl pra suprimir os leaks da readline()
	free(env_var);
}
