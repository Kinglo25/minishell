/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmajerus <lmajerus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 13:49:34 by lmajerus          #+#    #+#             */
/*   Updated: 2022/03/02 19:28:57 by lmajerus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	trim_tokens(t_token *head)
{
	while (head)
	{
		if (check_syntax(head))
			return (0);
		remove_quotes(head->data);
		head = head->next;
	}
	return (1);
}

static int	identify_type(char *str, t_token *tmp)
{
	if (!ft_strncmp(str, "|", 1))
		return (tmp->type_size = 1, PIPE);
	if (!ft_strncmp(str, ">>", 2))
		return (tmp->type_size = 2, REDIR_OUT);
	if (!ft_strncmp(str, ">", 1))
		return (tmp->type_size = 1, REDIR_OUT);
	if (!ft_strncmp(str, "<<", 2))
		return (tmp->type_size = 2, REDIR_IN);
	if (!ft_strncmp(str, "<", 1))
		return (tmp->type_size = 1, REDIR_IN);
	if (!ft_strncmp(str, "\t", 1))
		return (tmp->type_size = 1, SPACE);
	if (!ft_strncmp(str, "\n", 1))
		return (tmp->type_size = 1, SPACE);
	if (!ft_strncmp(str, "\r", 1))
		return (tmp->type_size = 1, SPACE);
	if (!ft_strncmp(str, "\v", 1))
		return (tmp->type_size = 1, SPACE);
	if (!ft_strncmp(str, "\f", 1))
		return (tmp->type_size = 1, SPACE);
	if (!ft_strncmp(str, " ", 1))
		return (tmp->type_size = 1, SPACE);
	return (tmp->type_size = 0, OTHER);
}

int	ft_strtok(char *str, t_token **head)
{
	char	*tmp;
	t_token	tmp_token;

	tmp = str;
	while (str && *str)
	{
		tmp_token.type = identify_type(str, &tmp_token);
		if (tmp_token.type && tmp != str)
			token_add_back(head, create_token(tmp_token, tmp, str - tmp, 1));
		if (tmp_token.type)
		{
			if (tmp_token.type != SPACE)
				token_add_back(head,
					create_token(tmp_token, str, tmp_token.type_size, 0));
			str += tmp_token.type_size;
			tmp = str;
		}
		else if ((*str == '\"' || *str == '\'') && !find_next_quotes(&str))
			return (ft_error("Syntax error\n"));
		else
			str++;
	}
	if (tmp != str)
		token_add_back(head, create_token(tmp_token, tmp, str - tmp, 1));
	return (!trim_tokens(*head));
}
