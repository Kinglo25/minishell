/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtournay <mtournay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 10:47:50 by mtournay          #+#    #+#             */
/*   Updated: 2022/03/24 12:55:32 by mtournay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/exec.h"

char	*cmd_path(char **env, char *cmd) //check malloc ??????
{
	int		i;
	char	**paths;

/*	./ path not working WIP
	paths = NULL;
	printf("CMD = %s\n", cmd);
	if(cmd[0] == '.' && cmd[1] == '/')
	{
		paths[0] = ft_strdup(cmd);
		printf("PATH: %s\n", paths[0]);
		if (!access(paths[0], F_OK) && !access(paths[0], X_OK))
		{
			printf("ACCES TO PHILO OK\n");
			return (paths[0]);
		}
	}*/
	i = 0;
	while (!ft_strnstr(env[i], "PATH=", 5))
		i++;
	env[i] = ft_substr(env[i], 6, ft_strlen(env[i]));
	paths = ft_split(env[i], ':');
	i = -1;
	while (paths[++i])
	{
		paths[i] = ft_strjoin(paths[i], "/");
		paths[i] = ft_strjoin(paths[i], cmd);
		if (!access(paths[i], F_OK) && !access(paths[i], X_OK))
			return (paths[i]);
		free(paths[i]);
	}
	return (0);
}

//Not sure if enough
void	ft_exec_error(char *str)
{
	perror(str);
	while (str)
	exit(EXIT_FAILURE);
}





void	check_in_out_redir(t_mini *shell, t_pipes *p, int i)
{
	if (shell->cmds[i].redir_in.file_name)
	{
		p->f_in = open(shell->cmds[i].redir_in.file_name, shell->cmds[i].redir_in.flags);
		if (p->f_in < 0)
			ft_exec_error("Open");
	}
	else
		p->f_in = 0;

	if (shell->cmds[i].redir_out.file_name)
	{
		p->f_out = open(shell->cmds[i].redir_out.file_name, shell->cmds[i].redir_out.flags);
		if (p->f_out < 0)
			ft_exec_error("Open");
	}
	else
		p->f_out = 1;
}

void	close_pipe(int *end)
{
	close(end[0]);
	close(end[1]);
}

void	child_process(t_mini *shell, t_pipes *p, int i)
{
	int		ret;

	if (p->f_out != 1)
		dup2(p->f_out, 1);
	if (p->f_in != 0)
		dup2(p->f_in, 0);
	if (i > 0)
	{
		dup2(p->old_end[0], p->f_in);
		close_pipe(p->old_end);
	}
	if (i + 1 < shell->nb_cmd)
	{
		dup2(p->new_end[1], p->f_out);
		close_pipe(p->new_end);
	}
	ret = ft_bin(&(shell->env), shell->cmds[i].av, *p); //cmd[i]
	if (ret == 1)
		exit(0);
	if (ret == 8)
	{
		if (execve(cmd_path(shell->env, shell->cmds[i].av[0]), shell->cmds[i].av, shell->env) == -1)
			ft_exec_error("Execve");
	}
}

void	parent_process(t_mini *shell, t_pipes *p, int i, pid_t pid)
{
	if (i > 0)
		close_pipe(p->old_end);
	if (i + 1 < shell->nb_cmd)
	{
		p->old_end[0] = p->new_end[0];
		p->old_end[1] = p->new_end[1];
	}
	waitpid(pid, NULL, 0);
}

void	ft_exec_cmd(t_mini *shell)
{
	int 	i;
	pid_t 	pid;
	t_pipes p;

	i = -1;
	while (++i < shell->nb_cmd)
	{
		if (i < shell->nb_cmd - 1) //there is a next cmd
			pipe(p.new_end); //0 read, 1 write
		check_in_out_redir(shell, &p, i);
		pid = fork();
		if (pid == 0)	//child
			child_process(shell, &p, i);
		else			//parent
			parent_process(shell, &p, i, pid);	
	}
	if (shell->nb_cmd > 1)
		close_pipe(p.old_end);
}