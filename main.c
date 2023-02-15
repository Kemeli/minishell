/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaiane- < kdaiane-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 00:25:47 by kdaiane-          #+#    #+#             */
/*   Updated: 2023/02/15 14:20:28 by kdaiane-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	not_regex(char *str)
// {
// 	if (ft_strchr("?$><|&", str)) 
// 		return (0);
// 	return (1);
// }
// //ideia: criar aqui uma chave que ligaria quando um regex é encontrado, para depois
// //checar a chave e tratar caso necessário



// //separa em tokens
// // falta tratar casos de cmd e caracteres sem espaço.
// void	parser(char *input)
// {
// 	t_token	*token;
// 	char	**temp;

// 	temp = ft_split(input, ' ');
// 	while (not_regex(temp[i]))
// 	{
// 		token->cmd[i] = temp[i];
// 		i++;
// 	}

// 	//print matriz
// 	for (int j = 0; token->cmd[j]; j++)
// 		printf ("%s\n", token->cmd[j]);
// }

char	*get_input()
{
    char    *input;
    char    *prompt;

    prompt = "minishell> ";
    input = readline(prompt);

    //print input -- tirar depois
    printf("%s\n", input);
	//chama a função que vai separar tudo em tokens
	return (input);
}

int main()
{
	t_token *list;
	char	*input;

	list = NULL;
    input = get_input();
	lexer(input, list);
}
