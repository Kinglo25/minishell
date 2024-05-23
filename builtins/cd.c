/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtournay <mtournay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 13:08:27 by mtournay          #+#    #+#             */
/*   Updated: 2022/04/05 15:43:25 by mtournay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"
#include "exec.h"

int ft_cd(char **cmd) 
{
    char *path;
    // char s[100]; //debug

    // printf("start: %s\n", getcwd(s, 100)); //debug
    if (!cmd[1])
        path = getenv("HOME");
    else if (cmd[2]) 
    {
        error_mess("minishell: cd: ", "too many arguments", 0, 1);
        return (1);
    }
    else if (cmd[1][0] == '~')
        path = ft_strjoin(getenv("HOME"), &cmd[1][1]);
    else
        path = cmd[1];
    if (chdir(path) != 0) 
    {
        error_mess("minishell: cd: ", "no such file or directory: ", path, 1);
        return (1);
    }
    // printf("end: %s\n", getcwd(s, 100)); //debug
    return (1);
}