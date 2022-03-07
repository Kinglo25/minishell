/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmajerus <lmajerus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 11:36:29 by lmajerus          #+#    #+#             */
/*   Updated: 2022/03/07 15:45:52 by lmajerus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	shell_loop(t_mini *shell, char **input)
{
	while (1)
	{
		*input = readline("Minishell 🐚 ");
		add_history(*input);
		*input = ft_strtrim(*input, " ");
		if (!*input || !**input)
			continue ;
		shell->nb_cmd = 0;
		parser(shell, input);
		free(*input);
	}
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
