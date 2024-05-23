#include "minishell.h"
#include "builtins.h"
#include "exec.h"

int	ft_unset(char ***env, char **cmd)
{
	int	i;
	int	j;
	int	len;

	i = 1;
	while (cmd[i])
	{
		len = ft_strlen(cmd[i]);
		j = 0;
		while ((*env)[j])
		{
			if (ft_strlen((*env)[j]) >= len && (*env)[j][len] == '=' && !ft_strncmp(cmd[i], (*env)[j], len))
			{
				free((*env)[j]);
				while ((*env)[j + 1])
				{
					(*env)[j] = (*env)[j + 1];
					j++;
				}
				(*env)[j] = NULL;
				// printf("last = %s\n", (*env)[j]); //debug
				// printf("%s found and deleted\n", cmd[i]); //debug
			}
			j++;
		}
		i++;
	}
	return (1);
}