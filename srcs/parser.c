/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmajerus <lmajerus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 12:07:30 by lmajerus          #+#    #+#             */
/*   Updated: 2022/03/02 19:14:56 by lmajerus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parser(t_mini *shell, char **input)
{
	t_token	*head;

	head = NULL;
	ft_strtok(*input, &head);
	while (head)
	{
		printf("%s\n", head->data);
		printf("%i\n", head->type);
		head = head->next;
	}
	shell->tktk = 3;
	return (1);
}
