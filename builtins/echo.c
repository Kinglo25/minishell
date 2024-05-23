/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtournay <mtournay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 17:23:42 by mtournay          #+#    #+#             */
/*   Updated: 2022/04/05 16:19:59 by mtournay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"
#include "exec.h"

int ft_check_n(char *str)
{
  int i;

  if (!str || str[0] != '-')
    return (0);
  i = 1;
  while (str[i])
  {
    if (str[i] != 'n')
      return (0);
    i++;
  }
  return (1);
}

int ft_echo(char **cmd)
{
  int i;
  int j;
  int n;

  // printf("in: %s\n", cmd[1]); //debug
  if (!cmd[1])
  {
    write(1, "\n", 1);
    return (0);
  }
  n = 0;
  while (ft_check_n(cmd[n + 1]))
    n++;
  i = 1 + n;
  while (cmd[i])
  {
    j = 0;
    while (cmd[i][j])
    {
      if (cmd[i][j] == '\\' && cmd[i][j + 1] == '\\' && cmd[i][j + 2] == 'n')
	    {
	    	write(1, "\n", 1);
	      j += 2;
	    }
      else
        write(1, &cmd[i][j], 1);
      j++;
    }
    if (cmd[i + 1])
      write(1, " ", 1);
    i++;
  }
  if (!n)
    write(1, "\n", 1);
  return (0);
}