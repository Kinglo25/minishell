/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmajerus <lmajerus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 11:44:22 by lmajerus          #+#    #+#             */
/*   Updated: 2022/03/02 18:21:05 by lmajerus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

# define OTHER 0
# define PIPE 1
# define REDIR_IN 2
# define REDIR_OUT 3
# define SPACE 4

typedef struct s_token
{
	char	*data;
	int		data_size;
	int		type;
	int		type_size;
	void	*next;
}			t_token;

typedef struct s_cmd
{
	char	*data;

}			t_cmd;

typedef struct s_mini
{
	t_cmd	cmds;
	char	**envp;
	int		tktk;
}			t_mini;

// parser.c

int		parser(t_mini *shell, char **input);

// ft_str_tok.c

int		ft_strtok(char *str, t_token **head);

// ft_strtok_utils.c

int		find_next_quotes(char **str);
char	*ft_substr(char const *s, unsigned int start, size_t len);
t_token	*last_token(t_token *head);
void	token_add_back(t_token **head, t_token *new);
t_token	*create_token(t_token tmp, char *str, int size, int x);

// utils.c

int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *s);
void	ft_putstr_fd(char *s, int fd);
int		ft_error(char *error_msg);

#endif
