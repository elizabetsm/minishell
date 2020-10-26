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
	char *curdir;
	char 	*curhome;
	int i;
	int ret;

	i = 0;
	ret = 0;
	st->b_trig = 1;
	curhome = ft_memalloc(sizeof(char *) * 30);
	while (i < 2)
	{
		ft_putstr("aa");
		curhome[ret] = st->dir[ret];
		ret++;
		if (st->dir[ret] == '/')
			i++;
	}
	curhome[ret] = '\0';
	if (!st->args[1])
	{
		chdir(curhome);
	}
	else if (st->args[1][0] == '~')
	{
		i = 0;
		ret = 0;
		curdir = ft_memalloc(sizeof(char) * 15);
		while (st->args[1][i]) {
			if ((st->args[1][i] > 96 && st->args[1][i] < 123) ||
			(st->args[1][i] < 91 && st->args[1][i] > 65)) {
				curdir[ret] = st->args[1][i];
				ret++;
			}
			i++;
		}
		curdir[ret] = '\0';

		ret = chdir(curdir);
	}
	else if ((ret = chdir(st->args[1]))!= 0)
	{
		ft_putstr("cd: no such file or directory: ");
		ft_putstr(st->args[1]);
		ft_putchar('\n');
	}
//	ft_memdel((void **)curhome);
}
