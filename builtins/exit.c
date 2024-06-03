#include "minishell.h"
#include "builtins.h"
#include "exec.h"

static int	ft_str_isnum(char *s)
{
	int	i;

	i = 0;
	if (s[0] == '+' || s[0] == '-')
		i++;
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9' || s[i] == '\'' || s[i] == '\"')
			return (0);
		i++;
	}
	return (1);
}

void	ft_exit(t_mini *shell, int i)
{
	int exit_code;

	write(1, "exit\n", 5);
	if (i != -1 && shell->cmds[i].av[1] && shell->cmds[i].av[2])
	{
		write(2, "minishell: exit: too many arguments\n", 36);
		exit_code = 1;
	}
	else if (i != -1 && shell->cmds[i].av[1])
	{
		if (ft_str_isnum(shell->cmds[i].av[1]))
			exit_code = ft_atoi(shell->cmds[i].av[1]);
		else
		{
			write(2, "minishell: exit: ", 17);
			ft_putstr_fd(shell->cmds[i].av[1], 2);
			write(2, ": numeric argument required\n", 28);
			exit_code = 2;
		}
	}
	else
		exit_code = 0;
	if (shell->nb_cmd > 0)
		free_cmds(shell->cmds, shell->nb_cmd);
	free_env(shell->env);
	exit(exit_code);
}