/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaiane- < kdaiane-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 00:24:02 by kdaiane-          #+#    #+#             */
/*   Updated: 2023/02/20 22:09:12 by kdaiane-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft/libft.h"
#include <stdlib.h>

# define SEPARATOR -1
# define SPACE ' '

//vou deixar flags (-l) como argumento por enquanto, se nos builtins precisar
// especificamos depois
// conflito: variavel de ambiente também pode ser argumento de comando, então 
//acho melhor deixar fora por enquanto
//quando passada sozinha a env_var deve printar seu conteudo e aparecer msg de comando invalido 
enum e_token_type
{
	ZERO, //pq eu ia comparar com numero e eventualmente ia ser zero, mas da pra ver de tirar
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


typedef struct s_env_utils
{
	char	*env_var;
	char	*test;
	char	*pointer;
	char	*new_input;
	char	*temp;
}	t_env_utils;


typedef struct s_token
{
	char	*cmd;
	int		type;
	struct s_token	*next;
	struct s_token	*prev;
} t_token;

typedef struct s_env
{
	int	expand_var;
} t_env;

int main();
t_token	*lexer(char **input, t_token *list);
char	**get_input(t_env *env_var);
// char	**get_input_matrix(char *input);
void	env_var_checker(t_token *list, t_env *env_var);
int		opened_quotes(char *input, t_env *env_var);
char	*get_expanded_var(char *input, t_env *env_var);


void	free_matrix(char **input);
void	free_list(t_token *list);

#endif