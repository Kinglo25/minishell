/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtournay <mtournay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 11:59:59 by mtournay          #+#    #+#             */
/*   Updated: 2022/02/14 17:44:59 by mtournay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "libft/libft.h"

int	cmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	return (0);
}

void	free_varenv(char **var, char *last)
{
	int	j;

	j = 0;
	while (cmp(var[j], last))
		j++;
	j++;
	while (var[j])
	{
		free(var[j]);
		j++;
	}
	free(var);
}

int	ncmp(char *s1, char *s2, size_t n)
{
	int	i;

	i = 0;
	while ((s1[i] || s2[i]) && n > 0)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
		n--;
	}
	return (0);
}

int	nl_convert(char **s)
{
	char	*ret;
	int		b;
	int		i;
	int		j;

	i = 0;
	j = 0;
	b = 0;
	ret = malloc(sizeof(char) * ft_strlen(*s) + 1);
	if (!ret)
		return (0);
	while ((*s)[i])
	{
		ret[j] = (*s)[i];
		if ((*s)[i] == '\\' && (*s)[i + 1] == 'n')
		{
			b = 1;
			ret[j] = '\n';
			i++;
		}
		i++;
		j++;
	}
	ret[j] = '\0';
	if (!b)
	{
		free(ret);
		return (1);
	}
	*s = ret;
	return (1);
}
																	// dans le parsing il faut remplacer les char \n par un vrai newline
int	ft_echo(char *line, int opt, char **env)                    // (opt = 1) = -n / else opt = 0
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	if (!nl_convert(&line))
		return (0);
	if (!line)
	{
		if (!opt)
			write(1, "\n", 1);
		return (1);
	}
	if (line[i] == '$')
	{
		if (!line[i + 1])
			write(1, "$", 1);
		else
		{
			len = ft_strlen(line);
			while (env[j])
			{
				if (!ncmp(line, env[j], len))
				{
					if (env[j][++len] == '=')
						break ;
				}
				j++;
			}
			ft_putstr_fd(env[j] + len, 1);
			len = ft_strlen(env[j]);
		}
	}
	else
		ft_putstr_fd(line, 1);
	if (opt && env[j][len - 1] != '\n')
		write(1, "%%", 1);
	return (1);
}

int	ft_unset(char ***env, char *var)
{
	int		i;
	char	**ret;

	i = 0;
	while((*env)[i])
		i++;
	ret = malloc(sizeof(char *) * i);
	if (!ret)
		return (0);
	i = 0;
	while(cmp((*env)[i], var) && (*env)[i])
	{
		ret[i] = (*env)[i];
		i++;
	}
	if (!(*env)[i])
	{
		free(ret);
		return (1);
	}
	i++;
	free((*env)[i -1]);
	while ((*env)[i])
	{
		ret[i - 1] = (*env)[i];
		i++;
	}
	ret[i - 1] = NULL;
	free(*env);
	*env = ret;
	return (1);
}

int	ft_export(char ***env, char *var)			//	il faudra free les variables d'env
{
	char	**ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while ((*env)[i])
		i++;
	ret = malloc(sizeof(char *) * (i + 2));
	if (!ret)
		return (0);
	while (j < i)
	{
		ret[j] = (*env)[j];
		j++;
	}
	ret[i] = ft_strdup(var);	
	if (!ret[i])
		return (0);
	i++;
	ret[i] = NULL;
	free(*env);
	*env = ret;
	return (1);
}

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

int	dup_env(char **env, char ***var_env)
{
	int	i;

	i = 0;
	while(env[i])
		i++;
	*var_env = malloc(sizeof(char *) * (i + 1));
	if (!var_env)
		return (0);
	i = 0;
	while (env[i])
	{
		(*var_env)[i] = env[i];
		i++;
	}
	(*var_env)[i] = NULL;
	return (1);
}

int main(int argc, char **argv, char *envp[])
{
	int i;
	char **var_env;
	char *last;


	argc = 0;
	i = 0;
	while (envp[i])
		i++;
	last = ft_strdup(envp[i - 1]);
	if (!dup_env(envp, &var_env))
		return (0);
	if (!ft_export(&var_env, argv[1]))
		return (0);
	ft_env(var_env);
	ft_unset(&var_env, argv[1]);
	write(1, "\n", 1);
	write(1, "\n", 1);
	write(1, "\n", 1);
	write(1, "\n", 1);
	write(1, "\n", 1);
	ft_env(var_env);
	free_varenv(var_env, last);
	// ft_echo(argv[1], 0, var_env);
}
