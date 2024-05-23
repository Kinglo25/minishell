#include "minishell.h"
#include "builtins.h"
#include "exec.h"

int ft_pwd(char **cmd, t_pipes p)
{
    char cwd[PATH_MAX];

    if (!getcwd(cwd, sizeof(cwd)))
    {
        error_mess("minishell : pwd: getcwd failed", 0, 0, 1);
        return (1);
    }
   	ft_putendl_fd(cwd, p.f_out);
    return (1);
}