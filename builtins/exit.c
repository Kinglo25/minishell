#include "minishell.h"

static int	ft_str_isnum(char *s)
{
	int	i;

	i = 0;
	if (s[0] == '+')
		i++;
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9' || s[i] == '\'' || s[i] == '\"')
			return (0);
		i++;
	}
	return (1);
}

void	ft_exit(char **cmd)
{
	write(1, "exit\n", 5);
	if (cmd[1] && cmd[2])
	{
		error_mess("minishell: exit: too many arguments", 0, 0, 1);
		exit(1);
	}
	if (cmd[1])
	{
		if (ft_str_isnum(cmd[1]))
			exit(ft_atoi(cmd[1]));
		else
		{
			error_mess("minishell: exit: ", cmd[1], ": numeric argument required", 1);
			exit(2);
		}
	}
	exit(0);
}