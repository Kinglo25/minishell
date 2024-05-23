#include "minishell.h"
#include "builtins.h"
#include "exec.h"


int check_var_exist(char **env, char *str)
{
	int	i;
	int	len;

	len = 0;
	while (str[len] != '=')
		len++;
	i = 0;
	while (env[i])
	{
		if (ft_strlen(env[i]) >= len && env[i][len] == '=' && !ft_strncmp(str, env[i], len))
			return (i);
		i++;
	}
	return (-1);
}

int	check_var_name(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
	{
		error_mess("minishell: export: ", str,": not a valid identifier", 1);
		return (0);
	}
	while (str[i] != '=' && str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
		{
			error_mess("minishell: export: ", str,": not a valid identifier", 1);
			return (0);
		}
		i++;
	}
	if (str[i] == '=')
		return (1);
	return (0);
}

char **env_realloc(char **env, char *var, size_t size)
{
    char **new;
    int i;

    i = 0;
    new = malloc(size * sizeof(char *));
    if (!new)
        return (NULL);
    while (env[i])
    {
        new[i] = ft_strdup(env[i]);
        if (!new[i])
        {
			i--;
            while (i > 0) // free all
            {
				free(new[i]);
				i--;
			}
            free(new);
            return (NULL);
        }
        free(env[i]);
        i++;
    }
	free(env);
	new[i] = ft_strdup(var);
	new[i + 1] = NULL;
    return (new);
}

int	ft_export(char ***env, char **cmd)
{
	int	env_count;
	int	i;
	int	j;

	i = 1;
	while (cmd[i])
	{
		if (check_var_name(cmd[i]))
		{
			j = check_var_exist(*env, cmd[i]);
			if (j != -1)
			{
				// printf("%s replaced by %s\n", (*env)[j], cmd[i]); //debug
				free((*env)[j]);
				(*env)[j] = ft_strdup(cmd[i]);
			}
			else
			{
				// printf("integrated\n"); //debug
				env_count = 0;
				while ((*env)[env_count] != NULL) 
					env_count++;
				*env = env_realloc(*env, cmd[i], sizeof(char *) * (env_count + 2));
				if (!*env)
					exit(0);
			}
		}
		i++;
	}
	return (1);
}