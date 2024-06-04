#include "minishell.h"
#include "builtins.h"
#include "exec.h"

int	ft_env(char **env, char **cmd, int pfd)
{
	int	i;

	if (cmd[1])
	{
		write(2, "minishell: env: too many arguments\n", 35);
		return (1);
	}
	i = 0;
	while (env[i])
	{
		ft_putendl_fd(env[i], pfd);
		i++;
	}
	return (0);
}
