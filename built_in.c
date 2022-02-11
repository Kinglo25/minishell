/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtournay <mtournay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 14:37:18 by mtournay          #+#    #+#             */
/*   Updated: 2022/02/11 12:40:00 by mtournay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "libft/libft.h"

void	ft_env(char **env)
{
	int	i;
	int	len;
	
	i = 0;
	while (env[i])
	{
		len = ft_strlen(env[i]);
		write(1, env[i], len);
		write(1, "\n", 1);
		i++;
	}
}

int pwd(char **buf)
{
	int		i;

	i = 1;

	*buf =  malloc(sizeof(char) *i );
	if (!buf)
		return (0);
	while(!getcwd(*buf,i))
	{
		free(*buf);
		i++;
		*buf =  malloc(sizeof(char) * i);
		if (!*buf)
			return (0);
	}
	return (1);
}

static char	*dot_dot(char *buf, char *ret)
{
	int		i;
	int		j;

	j = 0;
	i = ft_strlen(buf);
	while (buf[i] != '/')
		i--;
	ret = malloc(sizeof(char) * i + 10);
	if (!ret)
		return (0);
	while (j < i)
	{
		ret[j] = buf[j];
		j++;
	}
	ret[j] = '\0';
	return (ret);
}

int	ft_cd(char *dest)
{
	char *buf;
	char *new_dest;

	if (!pwd(&buf))
		return (0);
	if (!ft_strncmp(dest, "..", 3))
	{
		new_dest = dot_dot(buf, new_dest);
		if (!new_dest)
			return (0);
		chdir(new_dest);
		free(new_dest);
		free(buf);
		return (1);
	}
	if (dest[0] == '/')
	{
		if (chdir(dest) == -1)
			printf("cd: no such file or directory: %s\n", dest);
		free(buf);
	}
	else
	{
		new_dest = ft_strjoin(buf, dest);
		if (!new_dest)
			return (0);
		if (chdir(dest) == -1)
			printf("cd: no such file or directory: %s\n", dest);
		free(new_dest);
		free(buf);
	}
	return (1);
}

