#include "minishell.h"
#include "builtins.h"
#include "exec.h"

int	ft_unset(char ***env, char **cmd)
{
	int		i;
	int		j;
	size_t	len;

	i = 0;
	while (cmd[++i])
	{
		len = ft_strlen(cmd[i]);
		j = -1;
		while ((*env)[++j])
		{
			if (ft_strlen((*env)[j]) >= len && (*env)[j][len] == '='
			&& !ft_strncmp(cmd[i], (*env)[j], len))
			{
				free((*env)[j]);
				while ((*env)[j + 1])
				{
					(*env)[j] = (*env)[j + 1];
					j++;
				}
				(*env)[j] = NULL;
			}
		}
	}
	return (0);
}
