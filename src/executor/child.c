/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaiane- < kdaiane-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 20:11:30 by kdaiane-          #+#    #+#             */
/*   Updated: 2023/03/30 20:11:31 by kdaiane-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	change_fd(int file, int std_fd)
{
	dup2(file, std_fd);
	close (file);
}

static void	fd_redir(t_redir *redirect, t_exec *exec, int i)
{
	if (redirect->here_file)
		change_fd(redirect->here_file, STDIN_FILENO);
	if (redirect->infile && redirect->infile != -1)
		change_fd(redirect->infile, STDIN_FILENO);
	if (redirect->outfile && redirect->outfile != -1)
		change_fd(redirect->outfile, STDOUT_FILENO);
	if (!redirect->outfile && exec->to_process > 1)
		dup2 (exec->fd[i][1], STDOUT_FILENO);
	if (!redirect->infile && i > 0 && !redirect->here_file)
		dup2 (exec->fd[i - 1][0], STDIN_FILENO);
	close_fd(exec->fd);
}

void	child(t_exec *exec, t_redir *redir, t_token *aux, t_list *envp)
{
	int	is_builtin;

	fd_redir(redir, exec, exec->ended_proc);
	is_builtin = try_builtin(exec, &envp, aux, redir);
	if (exec->cmd && !exec->path)
		exec->path = get_path(exec->cmd[0], envp);
	if (exec->path && !is_builtin)
	{
		exec->envp_ms = envp_matrix(envp);
		execve(exec->path, exec->cmd, exec->envp_ms);
	}
	if (exec->cmd && !is_builtin)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(exec->cmd[0], 2);
		ft_putstr_fd(": no such file or directory\n", 2);
		free_exit (exec, redir, aux, envp);
		exit(127);
	}
	free_exit (exec, redir, aux, envp);
	exit(g_shell.exit_status);
}
