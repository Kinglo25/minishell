/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssenas-y <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:10:01 by ssenas-y          #+#    #+#             */
/*   Updated: 2024/06/04 16:10:06 by ssenas-y         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"
#include "exec.h"

int	ft_cd(char **cmd)
{
	char	*path;

	if (!cmd[1])
		path = getenv("HOME");
	else if (cmd[2])
	{
		write(2, "minishell: cd: too many arguments\n", 34);
		return (1);
	}
	else if (cmd[1][0] == '~')
		path = ft_strjoin(getenv("HOME"), &cmd[1][1]);
	else
		path = cmd[1];
	if (chdir(path) != 0)
	{
		perror(path);
		return (1);
	}
	return (0);
}
