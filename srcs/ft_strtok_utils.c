/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmajerus <lmajerus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 14:24:19 by lmajerus          #+#    #+#             */
/*   Updated: 2022/03/02 18:41:38 by lmajerus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_next_quotes(char **str)
{
	char	quotes;

	quotes = **str;
	(*str)++;
	while (**str)
	{
		if (**str == quotes)
			return (1);
		(*str)++;
	}
	return (0);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new;
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	new = malloc(sizeof(*s) * (len + 1));
	if (!new)
		return (NULL);
	new[len] = '\0';
	while (i < len && start + i < ft_strlen(s))
	{
		new[i] = s[start + i];
		i++;
	}
	return (new);
}

t_token	*last_token(t_token *head)
{
	while (head)
	{
		if (!head->next)
			return (head);
		head = head->next;
	}
	return (head);
}

void	token_add_back(t_token **head, t_token *new)
{
	if (!*head)
		*head = new;
	else
		last_token(*head)->next = new;
}

t_token	*create_token(t_token tmp, char *str, int size, int x)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->data = ft_substr(str, 0, size);
	new->data_size = size;
	if (!x)
		new->type = tmp.type;
	else
		new->type = OTHER;
	new->type_size = tmp.type_size;
	new->next = NULL;
	return (new);
}
