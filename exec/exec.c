#include "minishell.h"
#include "builtins.h"
#include "exec.h"

int	handle_redir(t_mini *shell, t_pipes *p, int i)
{
    if (shell->cmds[i].redir_in.doc)
        handle_heredoc(shell, p, i);
    if (shell->cmds[i].redir_in.file_name)
	{
		p->fd_in = open(shell->cmds[i].redir_in.file_name, shell->cmds[i].redir_in.flags);
        if (p->fd_in < 0)
		{
            perror(shell->cmds[i].redir_in.file_name);
            return (1);
        }
    }	
	if (shell->cmds[i].redir_out.file_name)
	{
		p->fd_out = open(shell->cmds[i].redir_out.file_name, shell->cmds[i].redir_out.flags);
		if (p->fd_out < 0)
		{
        	perror(shell->cmds[i].redir_out.file_name);
            return (1);
        }
    }
    return (0);
}

static void    handle_dup(t_mini *shell, t_pipes *p, int i)
{
	if (p->fd_out != 1)
        dup2(p->fd_out, 1);
    if (p->fd_in != 0)
    	dup2(p->fd_in, 0);
    if (i > 0)
	{
    	dup2(p->old_fd[0], p->fd_in);
        close_pipe(p->old_fd);
    }
	if (i < shell->nb_cmd - 1)
	{
        dup2(p->fd[1], p->fd_out);
        close_pipe(p->fd);
    }
}

static int exec(t_mini *shell, int i, t_pipes *p)
{
    char *cmd_path;

    p->fd_in = 0;
    p->fd_out = 1;
    if (handle_redir(shell, p, i))
        return(1);
    handle_dup(shell, p, i);
    if (ft_isbuiltin(shell->cmds[i].av[0])) 
        return(ft_exec_builtin(shell, i, p->fd_out));
    cmd_path = ft_cmd_path(shell->cmds[i].av[0]);
    execve(cmd_path, shell->cmds[i].av, shell->env);
    perror(cmd_path);
    return(1);
}

static void    handle_process(t_mini *shell, pid_t pid, t_pipes *p, int i)
{
    int status;

    if (pid == 0)
        exit(exec(shell, i, p));
    else
    {
        if (i > 0)
            close_pipe(p->old_fd);
        if (i < shell->nb_cmd - 1)
        {
            p->old_fd[0] = p->fd[0];
            p->old_fd[1] = p->fd[1];
        }
        waitpid(pid, &status, 0);
        g_es = WEXITSTATUS(status);
    }
}
void ft_exec_cmd(t_mini *shell)
{
    int		i;
    pid_t	pid;
    t_pipes	p;

    i = 0;
	if (shell->nb_cmd == 1 && ft_isbuiltin(shell->cmds[i].av[0]))
        exec_solo(shell, &p, i);
    else
    {
        while (i < shell->nb_cmd)
        {
            if (i < shell->nb_cmd - 1 && pipe(p.fd) == -1) 
            {
                perror("pipe");
                ft_exit(shell, -1);
            }
            pid = fork();
            if (pid == -1) 
            {
                perror("fork");
                ft_exit(shell, -1);
            }
            handle_process(shell, pid, &p, i);
            i++;
        }
    }
}
