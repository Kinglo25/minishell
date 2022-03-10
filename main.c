/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmajerus <lmajerus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 11:36:29 by lmajerus          #+#    #+#             */
/*   Updated: 2022/03/09 18:38:19 by lmajerus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		free(env[i++]);
	free(env);
	return ;
}

static char	**malloc_envp(char **envp, int i)
{
	char	**new;

	while (envp[i])
		i++;
	new = malloc(sizeof(char *) * i + 1);
	if (!new)
		return (NULL);
	new[i] = NULL;
	i = 0;
	while (envp[i])
	{
		new[i] = ft_strdup(envp[i]);
		if (!new[i])
		{
			while (i--)
				free(new[i]);
			free(new);
			return (NULL);
		}
		i++;
	}
	return (new);
}

static void	shell_loop(t_mini *shell, char **input)
{
	while (1)
	{
		shell->nb_cmd = 0;
		*input = readline("Minishell 🐚 ");
		add_history(*input);
		*input = ft_strtrim(*input, " ");
		if (!**input)
			continue ;
		if (!*input && write(2, "exit\n", 5))
			break ;
		shell->nb_cmd = 0;
		parser(shell, input);
		free(*input);
		// here you launch the cmd handler
		free_cmds(shell->cmds, shell->nb_cmd);
	}
	if (shell->nb_cmd > 0)
		free_cmds(shell->cmds, shell->nb_cmd);
}

int	main(int argc, char **argv, char **envp)
{
	t_mini	shell;
	char	*input;

	(void)argc;
	(void)argv;
	shell.env = malloc_envp(envp, 0);
	shell_loop(&shell, &input);
	free_env(shell.env);
}
