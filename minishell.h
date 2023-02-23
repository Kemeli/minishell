/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaiane- < kdaiane-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 00:24:02 by kdaiane-          #+#    #+#             */
/*   Updated: 2023/02/23 15:10:49 by kdaiane-         ###   ########.fr       */
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
	SYS_CMD = 1,
	BUILTIN = 2,
	ARGUMENT = 3,
	IN_REDIRECT = 4,
	OUT_REDIRECT = 5,
	PIPE = 6,
	HEREDOC = 7,
	HERE_ARG = 8,
	APPEND = 9,
	OUTFILE = 10,
	INFILE = 11
};

typedef	struct s_input_utils
{
	int		i;
	int		j;
	int		open_quotes;
}	t_input_utils;


typedef struct s_env_utils
{
	int		i;
	int		expand_var;
	int		var_size;
	int		open_quotes;
	char	*env_var;
	char	*test;
	char	*temp;
	char	*ch_join;
	char	*ch_cpy;
	char	*get_ret;
}	t_env_utils;


typedef struct s_token
{
	char	*cmd;
	int		type;
	struct s_token	*next;
	struct s_token	*prev;
} t_token;


int main();
t_token	*lexer(char **input, t_token *list);
char	**get_input(t_env_utils *env);
void	env_var_checker(t_token *list, t_env_utils *env);
int		opened_quotes(char *input);
char	*get_expanded_var(char *input, t_env_utils *env);
void	sintax(t_token *list);


void	free_matrix(char **input);
void	free_list(t_token *list);

#endif