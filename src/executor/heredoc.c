/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaiane- < kdaiane-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 20:11:57 by kdaiane-          #+#    #+#             */
/*   Updated: 2023/03/30 20:11:57 by kdaiane-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	print_heredoc(char **matrix, t_redir *redirect)
{
	int	i;

	i = -1;
	while (matrix[++i])
	{
		ft_putstr_fd(matrix[i], redirect->here_file);
		ft_putstr_fd("\n", redirect->here_file);
	}
}

static char	*heredoc(char **eof)
{
	char	*read;
	char	*input;
	int		i;

	i = 0;
	input = ft_calloc(sizeof (char *), 1);
	while (!g_shell.stop_loop)
	{
		read = readline(">");
		if (!read)
			break ;
		if (eof[i] && !ft_strncmp(read, eof[i], ft_strlen(eof[i])))
		{
			if (!eof[++i])
				break ;
			free (input);
			free(read);
			input = ft_calloc(sizeof (char *), 1);
		}
		else
			input = join_heredoc_input(input, read);
	}
	return (input);
}

static char	*start_heredoc(t_token **aux, t_redir *redir)
{
	char	*input;
	char	**eof;

	eof = eof_matrix(aux);
	set_ctrl_c_heredoc();
	input = heredoc(eof);
	set_listeners();
	free_matrix (eof);
	if (g_shell.stop_loop == 1)
	{
		free (input);
		g_shell.stop_loop = 0;
		redir->here_sig = -1;
		return (NULL);
	}
	return (input);
}

int	heredoc_handler(t_redir *redir, t_list *envp, t_token **aux)
{
	char	*input;
	char	**input_matrix;
	char	*file;
	int		i;

	i = -1;
	input = start_heredoc (aux, redir);
	if (input)
	{
		file = ft_strdup("__heredoc");
		redir->here_file = open
			(file, O_WRONLY | O_CREAT | O_EXCL | O_TRUNC, 0777);
		input = get_expanded_var (input, envp, 1);
		input_matrix = heredoc_matrix (input);
		while (input_matrix[++i])
			input_matrix[i] = cut_quotes(input_matrix[i]);
		print_heredoc (input_matrix, redir);
		free (input);
		free_matrix (input_matrix);
		close (redir->here_file);
		open (file, O_RDONLY);
		free (file);
		return (1);
	}
	return (0);
}
