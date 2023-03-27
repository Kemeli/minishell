/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaiane- < kdaiane-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 00:24:02 by kdaiane-          #+#    #+#             */
/*   Updated: 2023/03/27 16:15:04 by kdaiane-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <libft.h>
# include <stdlib.h>

# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <signal.h>

# define SEPARATOR -1
# define SPACE ' '
# define _XOPEN_SOURCE 700
# define BUFFER 4096

enum e_token_type
{
	ZERO,
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

typedef struct s_dollar
{
	int		key;
	char	*temp;
	char	*ret;
}	t_dollar;

typedef struct s_cut_quotes
{
	char	*new;
	int		db_quotes;
	int		sp_quotes;
}	t_cut_quotes;

typedef struct s_input_utils
{
	int		i;
	int		j;
	int		db_quotes;
	int		sp_quotes;
	char	*str;
}	t_input_utils;

typedef struct s_envar
{
	int		i;
	int		expand_var;
	int		var_size;
	int		open_quotes;
	char	*env_var;
	char	*test;
	char	*ch_join;
	char	*ch_cpy;
	char	*get_ret;
	char	*status;
	int		sp_quotes;
	int		db_quotes;
	char	*temp;
	char	*stt_join;
}	t_envar;

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
	int		to_process;
	int		ended_proc;
	int		**fd;
	int		pid;
	char	**envp_ms;
	char	**input;
	int		status;
	int		exit_status;
	int		is_built;
	int		valid_redir;
}	t_exec;

typedef struct s_token
{
	char			*cmd;
	int				type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_shell
{
	t_list	*envp_list;
	int		current_pid;

	int		exit_status;
	int		stop_loop;
}	t_shell;

extern t_shell	g_shell;

t_list	*make_envp_list(char **envp, t_list *envp_list);

/******************************************************************************\
* HANDLE INPUT																   *
\******************************************************************************/
char	**get_input(t_list *list_envp);
int		opened_quotes(char *input);
char	*input_separator(char *input, t_input_utils *in);
char	*handle_dollar(char *input);
char	*handle_quotes_dollar(char *input);

/******************************************************************************\
* ENVIRONMENTAL VARIABLE													   *
\******************************************************************************/

void	env_var_checker(t_token *list, t_envar *env);
char	*get_expanded_var(char *input, t_list *list_envp, int hd);
int		is_env_char(int c);
char	*get_env(char *var, t_list *list_envp);

/******************************************************************************\
* LEXER																		   *
\******************************************************************************/

t_token	*lexer(char **input, t_token *list);
int		sintax(t_token *list);

/******************************************************************************\
* EXECUTE																	   *
\******************************************************************************/

void	start_exec(t_token *list, t_list *envp_list);
int		redirector(t_token *aux, t_redirect *redir, t_list *envp);
int	heredoc_handler(t_redirect *redirect, t_list *envp, t_token **aux);
char	**heredoc_matrix(char *input);
char	*join_heredoc_input(char *input, char *read);
char	**eof_matrix(t_token **aux);
char	*get_path(char *cmd, t_list *envp_list);
t_token	*get_cmd_matrix(t_token *list, t_exec *exec);
void	child(t_exec *exec, t_redirect *redir, t_token *aux, t_list *envp);
char	**envp_matrix(t_list *list_envp);
void	start_fd(t_exec *exec);
void	close_fd(int **fd);
void	wait_processes(t_exec *exec);

/******************************************************************************\
* BUILTINS																	   *
\******************************************************************************/

int		try_builtin(
			t_exec *exec,
			t_list **envp,
			t_token *list,
			t_redirect *redir
			);
int		env_built(t_exec *exec, t_list **envp, t_token *list, t_redirect *redir);
int		ft_cd(char **cmd, t_list **envp_list);
int		ft_echo(char **cmd);
int		ft_env(t_list *envp_list, char **cmd);
int		ft_unset(char **cmd, t_list *envp_list);
int		ft_export(char **cmd, t_list **envp_list);
int		ft_exit(t_exec *exec, t_token *list, t_list *envp, t_redirect *redir);
int		ft_pwd(void);
int		status(char *msg1, char *msg2, char *msg3, int status);
int		check_valid_envar(char **cmd, char *msg1, char *msg3, int exp);

/******************************************************************************\
* FREE																		   *
\******************************************************************************/

void	free_int_mat(int **input);
void	free_matrix(char **input);
void	free_input_matrix(char **input, int i);
void	free_list(t_token *list);
void	free_exit(t_exec *exec, t_redirect *redir, t_token *aux, t_list *envp);
void	free_shell(void);
void	free_null(char **str);

/******************************************************************************\
* SIGNALS																	   *
\******************************************************************************/

void	handle_sigint(int sig);
void	handle_sigquit(int sig);
void	handle_heredoc_sigint(int sig);
void	set_listeners(void);
void	set_ctrl_c_heredoc(void);

#endif
