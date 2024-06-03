/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtournay <mtournay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 19:14:27 by mtournay          #+#    #+#             */
/*   Updated: 2022/04/06 16:43:59 by mtournay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"
#include "exec.h"

void	close_pipe(int *end)
{
	if (close(end[0]) == -1)
	{
		perror("close");
		exit(1);
	}
	if (close(end[1]) == -1)
	{
		perror("close");
		exit(1);
	}
}


void	signal_handler_heredoc(int signum)
{
	if (signum == SIGINT)
	{
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		unlink("heredoc");
		exit(1);
	}
}


char	*ft_cmd_path(char *cmd)
{
	int		i;
	char	**split_path;
	char	*cmd_path;
	char	*tmp;

	if (!access(cmd, F_OK) && !access(cmd, X_OK))
		return (cmd);
	split_path = ft_split(getenv("PATH"), ':');
	if (!split_path)
		return (cmd);
	tmp = ft_strjoin("/", cmd);
	i = 0;
	while (split_path[i])
	{
		cmd_path = ft_strjoin(split_path[i], tmp);
		if (!access(cmd_path, F_OK) && !access(cmd_path, X_OK))
		{
			free(tmp);
			return (cmd_path);
		}
		free(cmd_path);
		i++;
	}
	free(tmp);
	return (cmd);
}
