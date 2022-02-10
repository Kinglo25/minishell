/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtournay <mtournay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 14:37:18 by mtournay          #+#    #+#             */
/*   Updated: 2022/02/10 17:27:24 by mtournay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "libft/libft.h"

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

char	*dot_dot(char *buf, char *ret)
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
	printf("ret = %s\n", ret);
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
		dot_dot(buf, new_dest);
		if (!new_dest)
			return (0);
		chdir(new_dest);
		return (1);
	}
	if (chdir(dest) == -1)
		printf("cd: no such file or directory: %s\n", dest);
	return (1);
}

int main(int argc, char **argv)
{
	char *buf;

	argc = 0;	
	if (!pwd(&buf))
		return (1);
	printf("%s\n\n", buf);
	free(buf);

	if (!ft_cd(argv[1]))
		return (1);

	if (!pwd(&buf))
		return (1);
	printf("%s\n", buf);
	free(buf);
}