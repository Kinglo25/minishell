/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtournay <mtournay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 16:03:17 by mtournay          #+#    #+#             */
/*   Updated: 2022/04/06 16:44:03 by mtournay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <limits.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include <signal.h>
# include "minishell.h"
# include "exec.h"

int		ft_pwd(int pfd);
int		ft_cd(char **cmd);
int		ft_echo(char **cmd, int pfd);
int		ft_unset(char ***env, char **cmd);
int		ft_export(char ***env, char **cmd);
int		ft_env(char **env, char **cmd, int pfd);
void	ft_exit(t_mini *shell, int i);

#endif