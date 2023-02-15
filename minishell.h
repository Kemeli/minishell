/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaiane- < kdaiane-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 00:24:02 by kdaiane-          #+#    #+#             */
/*   Updated: 2023/02/15 23:05:23 by kdaiane-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft/libft.h"

// # define COMMAND
// # define ARGUMENT
// # define IN_REDIRECT "<"
// # define OUT_REDIRECT ">"
// # define PIPE "|"
// # define HEREDOC "<<"
// # define APPEND ">>"
// # define INFILE
// # define OUTFILE


enum e_token_type
{
	COMMAND,
	ARGUMENT,
	IN_REDIRECT,
	OUT_REDIRECT,
	PIPE,
	HEREDOC,
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
void	lexer(char *input, t_token *list);

#endif