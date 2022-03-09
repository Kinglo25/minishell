/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmajerus <lmajerus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 11:36:29 by lmajerus          #+#    #+#             */
/*   Updated: 2022/03/09 17:27:50 by lmajerus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	shell.envp = envp;
	shell_loop(&shell, &input);
	free(shell.envp);
}
