/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmajerus <lmajerus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 11:36:29 by lmajerus          #+#    #+#             */
/*   Updated: 2022/03/02 19:28:53 by lmajerus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	shell_loop(t_mini *shell, char **input)
{
	while (1)
	{
		*input = readline("Minishell 🐚 ");
		if (!*input)
			
		add_history(*input);
		parser(shell, input);
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
}
