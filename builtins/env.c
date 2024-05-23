#include "minishell.h"
#include "builtins.h"
#include "exec.h"

int	ft_env(char **env, char **cmd, t_pipes p)
{
	int	i;

	if (cmd[1])
	{
		write(2, "Too many arguments\n", 19);
		return (1);
	}
	i = 0;
	while (env[i])
	{
		ft_putendl_fd(env[i], p.f_out);
		i++;
	}
	return (1);
}