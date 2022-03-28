/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtournay <mtournay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 11:48:45 by mtournay          #+#    #+#             */
/*   Updated: 2022/03/24 16:02:33 by mtournay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

#include "minishell.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include <signal.h>



// added struct
typedef struct s_pipes
{
	int		new_end[2];
	int		old_end[2];
	int 	f_in;
	int		f_out;
}				t_pipes;

//	pipes prototypes
char		*cmd_path(char **env, char *cmd);
int			ft_execute(char **cmd, char **envp); 
void		ft_exec_error(char *str);
void		ft_exec_cmd(t_mini *shell);

int			ft_bin(char ***env, char **cmd, t_pipes p); //add p




int     get_cd(char **buf);
int	    ft_pwd(char **cmd, t_pipes p); //add p
int	    ft_cd(char **cmd);
int	    ft_echo(char **cmd, char **env);
int	    ft_unset(char ***env, char **cmd);
int	    ft_export(char ***env, char **cmd);
int	    ft_env(char **env, char **cmd, t_pipes p); //add p

int 	cmp(char *s1, char *s2);
int	    ncmp(char *s1, char *s2, size_t n);
int	    nl_convert(char **s);
int	    dup_env(char **env, char ***var_env);
void	free_varenv(char **var, char *last);

int 	bin_cmd(char ***env, char **cmd);

char	*cat_dup(char *dst, char *src);



#endif