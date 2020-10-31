/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 17:42:58 by efleta            #+#    #+#             */
/*   Updated: 2020/10/30 17:43:00 by efleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	get_not_null_paths(t_struct *st, int i)
{
	int		j;
	int		k;
	char	*p;

	j = 5;
	k = 0;
	p = ft_memalloc(sizeof(char *) * ft_strlen(st->env[i]) + 1 - j);
	while (st->env[i][j])
	{
		p[k] = st->env[i][j];
		k++;
		j++;
	}
	st->paths = ft_strsplit1(p, ':');
	ft_memdel((void *)&p);
}

void	get_paths(t_struct *st, char *word)
{
	int		i;

	i = 0;
	while (st->env[i])
	{
		if (st->env[i][0] == word[0] && st->env[i][1] == word[1] &&
			st->env[i][2] == word[2] && st->env[i][3] == word[3] &&
			st->env[i][4] == '=')
		{
			get_not_null_paths(st, i);
			return ;
		}
		i++;
	}
	st->paths = (char **)ft_memalloc(sizeof(char *) * 2);
	st->paths[0] = ft_strjoin(&st->paths[0], &st->args[0], 1, 0);
	st->paths[1] = NULL;
}

void	parse_input(t_struct *st)
{
	st->args = ft_strsplit2(st->inp, " 	");
}
