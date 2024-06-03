#include "minishell.h"
#include "builtins.h"
#include "exec.h"

int ft_pwd(int pfd)
{
    char cwd[PATH_MAX];

    if (!getcwd(cwd, sizeof(cwd)))
    {
        perror("minishell : pwd");
        return (1);
    }
   	ft_putendl_fd(cwd, pfd);
    return (0);
}