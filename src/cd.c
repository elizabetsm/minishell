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

void	get_home(t_struct *st)
{
	int		ret;
	int		i;

	ret = 0;
	i = 0;
	st->h_trig = 1;
	st->homedir = ft_memalloc(sizeof(char *) * 30);
	while (i < 2 && st->dir[ret] != '\0')
	{
		st->homedir[ret] = st->dir[ret];
		ret++;
		if (st->dir[ret] == '/')
			i++;
	}
	st->homedir[ret] = '\0';
}

void	cd_home(t_struct *st)
{
	char	*curdir;
	char	*cddir;
	char	*cdddir;
	int		i;
	int		ret;

	ret = 0;
	i = 0;
	curdir = ft_memalloc(sizeof(char) * 15);
	while (st->args[1][i++])
	{
		if ((st->args[1][i] > 96 && st->args[1][i] < 123) ||
			(st->args[1][i] < 91 && st->args[1][i] > 65))
			curdir[ret++] = st->args[1][i];
	}
	curdir[ret] = '\0';
	cddir = ft_strdup("/");
	cddir = ft_strjoin(&st->homedir, &cddir, 0, 1);
	cdddir = ft_strjoin(&cddir, &curdir, 1, 1);
	if ((ret = chdir(cdddir)) != 0)
	{
		ft_putstr("cd: no such file or directory: ");
		ft_putstr(cdddir);
		ft_putchar('\n');

	}
	ft_memdel((void **)&cdddir);
}

void	cd_builtin(t_struct *st)
{
	int		ret;

	ret = 0;
	st->b_trig = 1;
	if (st->h_trig == 0)
		get_home(st);
	if (!st->args[1])
		chdir(st->homedir);
	else if (st->args[1][0] == '~')
		cd_home(st);
	else if ((ret = chdir(st->args[1])) != 0)
	{
		ft_putstr("cd: no such file or directory: ");
		ft_putstr(st->args[1]);
		ft_putchar('\n');
	}
}
