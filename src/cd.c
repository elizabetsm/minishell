/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 15:13:34 by efleta            #+#    #+#             */
/*   Updated: 2020/08/17 15:13:35 by efleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void cd_builtin(t_struct *st, char **env)
{
	char *dir;
	char *curdir;
	char *curpath;
	char **paths;
	char *newdir;
	int i;

	i = 0;
	if (st->args[1][0] == '~')
	{
		dir = getcwd(dir, sizeof(dir));
		paths = ft_strsplit(dir, '/');

//		while (paths[i])
//		{
//			curpath =
//		}
		newdir = ft_strjoin(dir, st->args[1]);
		chdir(newdir);
		return ;
	}
	else if (!st->args[1])
	{
		chdir("");
	}
	chdir(st->args[1]);
	st->b_trig = 1;
}
