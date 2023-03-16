/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatos-s <kmatos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 00:24:02 by kdaiane-          #+#    #+#             */
/*   Updated: 2023/03/15 21:44:03 by kmatos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <libft.h>
#include <stdlib.h>

# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <signal.h>

# define SEPARATOR -1
# define SPACE ' '
# define _XOPEN_SOURCE 700

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
	INFILE = 11,
	APPEND_OUT = 12
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

typedef struct s_redirect
{
	int	infile;
	int	outfile;
	int	fd_pipe;
	int	here_file;
}	t_redirect;

typedef struct s_exec
{
	char	**cmd;
	char	*path;
	int		process;
	int		**fd;
	int		pid;
	char	**envp_ms;
} t_exec;

typedef struct s_token
{
	char	*cmd;
	int		type;
	struct s_token	*next;
	struct s_token	*prev;
} t_token;

typedef struct s_shell
{
	t_list	*envp_list;
	char	*current_command;
	int		current_pid;
} t_shell;

extern t_shell	shell;

char	**get_input(t_list *list_envp);
int		opened_quotes(char *input);
void	env_var_checker(t_token *list, t_env_utils *env);
char *get_expanded_var(char *input, t_list *list_envp, int hd);
int		is_env_char(int c);
char	*get_env(char *var, t_list *list_envp);

t_token	*lexer(char **input, t_token *list);
void	sintax(t_token *list);

void	execute(t_token *list, t_list *envp_list, char **input);
void	redirector(t_token *aux, t_redirect *redirect, t_list *envp);
char	*get_path(char *cmd, t_list *envp_list);
t_token	*cmd_handler(t_token *list, t_exec *exec);


int		builtin_exec(t_exec *exec, t_list **envp_list);
char	**envp_matrix(t_list *list_envp);
t_list	*make_envp_list(char **envp, t_list *envp_list);
void	set_pwd(t_list *envp_list);
char	*handle_dollar(char *input);

void	free_int_mat(int **input);
void	free_matrix(char **input);
void	free_list(t_token *list);

void	free_shell(void);

/******************************************************************************\
* SIGNALS																	   *
\******************************************************************************/

void	handle_sigint(int sig);
void	handle_sigquit(int sig);
void	set_listeners(void);

#endif
