#include "minishell.h"
#include "builtins.h"
#include "exec.h"

int handle_heredoc(t_mini *shell, t_pipes *p, int i)
{
    t_here  *tmp;
    int     fd;

    tmp = shell->cmds[i].redir_in.doc;
    while (tmp)
    {
        if (!shell->cmds[i].av[0])
        {
            fd = open_heredoc(tmp);
			close(fd);
        }
        else
            p->fd_in = open_heredoc(tmp);
        tmp = tmp->next;
    }
	if (!shell->cmds[i].av[0])
		exit(0);
    return (0);
}

int open_heredoc(t_here *doc)
{
    char    *input;
    int     len;
    int     fd;

    len = ft_strlen(doc->delimiter) + 1;
	fd = open("heredoc", O_CREAT | O_WRONLY, 0666);
    while (1)
    {
        signal(SIGINT, signal_handler_heredoc);
        input = readline("<");
        if (!input)
        {
            close(fd);
            unlink("heredoc");
            exit(1);
        }
        if (!ft_strncmp(input, doc->delimiter, len))
        {
			free(input);
			close(fd);
			fd = open("heredoc", O_RDONLY, 0666);
			unlink("heredoc");
			return (fd);
		}
		ft_putendl_fd(input, fd);
        free(input);
    }
}