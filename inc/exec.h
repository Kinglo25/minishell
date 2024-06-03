/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtournay <mtournay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 19:09:45 by mtournay          #+#    #+#             */
/*   Updated: 2022/04/06 16:44:00 by mtournay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <signal.h>
# include <errno.h>
# include "minishell.h"
# include "builtins.h"

typedef struct s_pipes
{
	int	fd[2];
	int	old_fd[2];
	int	fd_in;
	int	fd_out;
}				t_pipes;

//builtins.c
int		ft_exec_builtin(t_mini *shell, int i, int pfd);
void	exec_solo(t_mini *shell, t_pipes *p, int i);
int		ft_isbuiltin(char *cmd);


//exec.c
int		handle_redir(t_mini *shell, t_pipes *p, int i);
void	ft_exec_cmd(t_mini *shell);

//heredoc.c
int handle_heredoc(t_mini *shell, t_pipes *p, int i);
int	open_heredoc(t_here *doc);

// Utils.c
void	signal_handler_heredoc(int signum);
char	*ft_cmd_path(char *cmd);
void	close_pipe(int *end);

#endif
