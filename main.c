/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtournay <mtournay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 11:59:59 by mtournay          #+#    #+#             */
/*   Updated: 2022/02/11 12:18:47 by mtournay         ###   ########.fr       */
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

int main(int argc, char **argv, char *envp[])
{
	int i;
	char **var_env;


	argc = 0;
	i = 0;
	while (envp[i])
	{
		i++;
	}

	var_env = malloc(sizeof(char *) *i + 1);
	var_env = envp;
	ft_env(var_env);
}
