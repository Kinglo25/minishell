/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmajerus <lmajerus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 13:17:50 by lmajerus          #+#    #+#             */
/*   Updated: 2022/02/10 16:20:45 by lmajerus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	main(int ac, char **av, char **env)
{
	char	*user_input;

	(void)ac;
	(void)av;
	(void)env;
	while (19)
	{
		user_input = readline("🐚 ");
		free(user_input);
	}
	return (0);
}
