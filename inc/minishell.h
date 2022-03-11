/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmajerus <lmajerus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 11:44:22 by lmajerus          #+#    #+#             */
/*   Updated: 2022/03/11 13:33:05 by lmajerus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>

# define OTHER 0
# define PIPE 1
# define REDIR_IN 2
# define REDIR_OUT 3
# define SPACE 4

int	g_exit_status;

typedef struct s_token
{
	char			*data;
	int				data_size;
	int				type;
	int				type_size;
	struct s_token	*next;
}			t_token;

typedef struct s_here
{
	char	*delimiter;
	void	*next;
}				t_here;
typedef struct s_red
{
	char	*file_name;
	int		flags;
	t_here	*doc;
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
	char	**env;
	int		nb_cmd;
}			t_mini;

// parser.c

int		parser(t_mini *shell, char **input);

// parser_utils.c

int		redir(t_red *red, t_token *head);
int		free_cmds(t_cmd *cmds, int nb_cmd);
int		free_tokens(t_token **head);
void	rl_replace_line(const char *text, int clear_undo);

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
void	*ft_calloc(size_t nmemb, size_t size);
void	ft_bzero(void *s, size_t n);
void	*ft_memset(void *s, int c, size_t n);
t_here	*ft_lstnew(void *content);
void	ft_lstadd_back(t_here **lst, t_here *new);
t_here	*ft_lstlast(t_here *lst);

// check_env_var.c

int		check_env_var(t_token *token);

#endif
