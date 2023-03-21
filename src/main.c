/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaiane- < kdaiane-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 00:25:47 by kdaiane-          #+#    #+#             */
/*   Updated: 2023/03/21 13:09:51 by kdaiane-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_shell	g_shell;

// Essa função vai sair
void	print_list(t_token *list)
{
	t_token	*aux;

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

	(void) argv;
	(void) argc;
	g_shell.envp_list = make_envp_list(envp, g_shell.envp_list);
	set_listeners();
	while (1)
	{
		list = NULL;
		input = get_input(g_shell.envp_list);
		if (input)
		{
			list = lexer(input, list);
			if (list && sintax(list))
			{
				start_exec(list, g_shell.envp_list);
				free_list(list);
			}
		}
	}
	free_shell();
}

void	free_shell(void)
{
	ft_lstclear(&g_shell.envp_list, &free);
	free(g_shell.envp_list);
	rl_clear_history();
}
