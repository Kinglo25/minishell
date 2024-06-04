#include "minishell.h"
#include "builtins.h"
#include "exec.h"

int	check_var_exist(char ***env, char *str)
{
	int		i;
	size_t	len;

	len = 0;
	while (str[len] != '=')
		len++;
	i = 0;
	while ((*env)[i])
	{
		if (ft_strlen((*env)[i]) >= len && (*env)[i][len] == '='
		&& !ft_strncmp(str, (*env)[i], len))
		{
			free((*env)[i]);
			(*env)[i] = ft_strdup(str);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_var_name(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
	{
		write(2, "minishell: export: ", 19);
		ft_putstr_fd(str, 2);
		write(2, ": not a valid identifier\n", 25);
		return (-1);
	}
	while (str[i] != '=' && str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
		{
			write(2, "minishell: export: ", 19);
			ft_putstr_fd(str, 2);
			write(2, ": not a valid identifier\n", 25);
			return (-1);
		}
		i++;
	}
	if (str[i] == '=')
		return (1);
	return (0);
}

char	**env_realloc(char **env, char *var, size_t size)
{
	char	**new;
	int		i;

	i = -1;
	new = malloc(size * sizeof(char *));
	if (!new)
		return (NULL);
	while (env[++i])
	{
		new[i] = ft_strdup(env[i]);
		if (!new[i])
		{
			i--;
			while (i-- > 0)
				free(new[i]);
			free(new);
			return (NULL);
		}
		free(env[i]);
	}
	free(env);
	new[i] = ft_strdup(var);
	new[i + 1] = NULL;
	return (new);
}

int	ft_export(char ***env, char **cmd)
{
	int	env_count;
	int	ret;
	int	i;

	i = 0;
	while (cmd[++i])
	{
		ret = check_var_name(cmd[i]);
		if (ret == -1)
			return (1);
		if (ret == 1)
		{
			if (check_var_exist(env, cmd[i]))
				return (0);
			else
			{
				env_count = 0;
				while ((*env)[env_count] != NULL)
					env_count++;
				*env = env_realloc(*env, cmd[i], sizeof(char *)
						* (env_count + 2));
			}
		}
	}
	return (0);
}
