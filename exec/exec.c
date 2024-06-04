/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssenas-y <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:11:49 by ssenas-y          #+#    #+#             */
/*   Updated: 2024/06/04 16:11:51 by ssenas-y         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"
#include "exec.h"

static void	handle_dup(t_mini *shell, t_pipes *p, int i)
{
	if (p->fd_out != 1)
		dup2(p->fd_out, 1);
	if (p->fd_in != 0)
		dup2(p->fd_in, 0);
	if (i > 0)
	{
		dup2(p->old_fd[0], p->fd_in);
		close_pipe(p->old_fd);
	}
	if (i < shell->nb_cmd - 1)
	{
		dup2(p->fd[1], p->fd_out);
		close_pipe(p->fd);
	}
}

static int	exec(t_mini *shell, int i, t_pipes *p)
{
	char	*cmd_path;

	p->fd_in = 0;
	p->fd_out = 1;
	if (handle_redir(shell, p, i))
		return (1);
	handle_dup(shell, p, i);
	if (ft_isbuiltin(shell->cmds[i].av[0]))
		return (ft_exec_builtin(shell, i, p->fd_out, 0));
	cmd_path = ft_cmd_path(shell->cmds[i].av[0]);
	execve(cmd_path, shell->cmds[i].av, shell->env);
	perror(cmd_path);
	return (1);
}

static void	handle_process(t_mini *shell, pid_t *pids, t_pipes *p, int i)
{
	if (pids[i] == 0)
		exit(exec(shell, i, p));
	else
	{
		signal(SIGINT, SIG_IGN);
		if (i > 0)
			close_pipe(p->old_fd);
		if (i < shell->nb_cmd - 1)
		{
			p->old_fd[0] = p->fd[0];
			p->old_fd[1] = p->fd[1];
		}
	}
}

int	wait_pids(pid_t *pids, int nb_pids)
{
	int	status;
	int	i;

	i = 0;
	while (i < nb_pids)
	{
		waitpid(pids[i], &status, 0);
		if (WIFEXITED(status))
			g_es = WEXITSTATUS(status);
		i++;
	}
	free(pids);
	return (0);
}

void	ft_exec_cmd(t_mini *shell)
{
	int		i;
	pid_t	*pids;
	t_pipes	p;

	pids = malloc(sizeof(pid_t) * shell->nb_cmd);
	if (shell->nb_cmd == 1 && ft_isbuiltin(shell->cmds[0].av[0]))
		return (exec_solo(shell, &p, 0));
	i = -1;
	while (++i < shell->nb_cmd)
	{
		signal(SIGINT, signal_handler);
		if (i < shell->nb_cmd - 1 && pipe(p.fd) == -1)
		{
			perror("pipe");
			ft_exit(shell, -1);
		}
		pids[i] = fork();
		if (pids[i] == -1)
		{
			perror("fork");
			ft_exit(shell, -1);
		}
		handle_process(shell, pids, &p, i);
	}
	wait_pids(pids, shell->nb_cmd);
}
