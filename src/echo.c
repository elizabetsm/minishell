/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 14:25:01 by efleta            #+#    #+#             */
/*   Updated: 2020/08/17 14:25:03 by efleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_env_line(t_struct *st, int i, int a)
{
	i++;
	while (st->env[a][i])
	{
		ft_putchar(st->env[a][i]);
		i++;
	}
}

void	print_env_var(t_struct *st)
{
	char	*tmp;
	int		i;
	int		a;

	i = 0;
	a = 0;
	tmp = ft_memalloc(sizeof(char *) * ft_strlen(st->args[1]));
	while (st->args[1][i++])
	{
		tmp[a] = st->args[1][i];
		a++;
	}
	tmp[a] = '\0';
	i = 0;
	a = 0;
	while (st->env[a])
	{
		while (st->env[a][i] != '=')
			i++;
		if (ft_strncmp(tmp, st->env[a], i) == 0)
			print_env_line(st, i, a);
		i = 0;
		a++;
	}
	ft_memdel((void **)&tmp);
}

void	print_line(t_struct *st, int i, int j)
{
	while (st->args[i][j])
	{
		if (st->args[i][j] == '"')
			j++;
		ft_putchar(st->args[i][j]);
		if (st->args[i][j] != '\0')
			j++;
	}
}

void	echo_builtin(t_struct *st)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	if (st->args[1])
	{
		if (st->args[1][0] == '$')
			print_env_var(st);
		else
		{
			while (st->args[i])
			{
				print_line(st, i, j);
				i++;
				j = 0;
				ft_putchar(' ');
			}
		}
	}
	st->b_trig = 1;
	ft_putchar('\n');
}
