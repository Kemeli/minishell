/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaiane- < kdaiane-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 00:24:02 by kdaiane-          #+#    #+#             */
/*   Updated: 2023/02/16 15:33:32 by kdaiane-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft/libft.h"

//vou deixar flags (-l) como argumento por enquanto, se nos builtins precisar
// especificamos depois
// conflito: variavel de ambiente também pode ser argumento de comando 	ENV_VAR, então 
//acho melhor deixar fora por enquanto
enum e_token_type
{
	ZERO,
	SYS_CMD,
	BUILTIN,
	ARGUMENT,
	IN_REDIRECT,
	OUT_REDIRECT,
	PIPE,
	HEREDOC,
	HERE_ARG,
	APPEND,
	OUTFILE,
	INFILE
};

typedef struct s_token
{
	char	*cmd;
	int		type;
	struct s_token	*next;
	struct s_token	*prev;
} t_token;

int main();
t_token	*lexer(char *input, t_token *list);

#endif