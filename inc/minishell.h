/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmajerus <lmajerus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 11:44:22 by lmajerus          #+#    #+#             */
/*   Updated: 2022/03/08 13:24:03 by lmajerus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

# define OTHER 0
# define PIPE 1
# define REDIR_IN 2
# define REDIR_OUT 3
# define SPACE 4

typedef struct s_token
{
	char			*data;
	int				data_size;
	int				type;
	int				type_size;
	struct s_token	*next;
}			t_token;

typedef struct s_red
{
	char	*file_name;
	int		flags;
}			t_red;

typedef struct s_cmd
{
	int		ac;
	char	**av;
	t_red	redir_in;
	t_red	redir_out;
}			t_cmd;

typedef struct s_mini
{
	t_cmd	*cmds;
	char	**envp;
	int		nb_cmd;
}			t_mini;

// parser.c

int		parser(t_mini *shell, char **input);

// parser_utils.c

int		redir(t_red *red, t_token *head);
int		free_cmds(t_cmd *cmds, int nb_cmd);
int		free_tokens(t_token **head);

// ft_str_tok.c

int		ft_strtok(char *str, t_token **head);

// ft_strtok_utils.c

int		find_next_quotes(char **str);
t_token	*last_token(t_token *head);
void	token_add_back(t_token **head, t_token *new);
t_token	*create_token(t_token tmp, char *str, int size, int x);

// utils.c

int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *s);
void	ft_putstr_fd(char *s, int fd);
int		ft_error(char *error_msg, int perror_flag);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *s);
void	*ft_memcpy(void *dest, const void *src, size_t n);
char	*ft_strtrim(char const *s1, char const *set);

// check_env_var.c

int		check_env_var(t_token *token);

#endif
