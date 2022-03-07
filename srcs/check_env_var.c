/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_env_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmajerus <lmajerus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 18:13:21 by lmajerus          #+#    #+#             */
/*   Updated: 2022/03/07 18:33:57 by lmajerus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_env_var(t_token *token)
{
	int	i;

	i = 0;
	while (token)
	{
		while (token->type == OTHER && token->data[i])
		{
			if (token->data[i] == '\'')
				while (token->data[++i] != '\'')
					;
			if (token->data[i] == '$')
				replace_env_var(token);
			i++;
		}
		token = token->next;
	}	
}

static void	replace_env_var(t_token *token)
{
	
}