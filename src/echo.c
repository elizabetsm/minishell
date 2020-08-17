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

void	echo_builtin(t_struct *st)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (st->args[i])
	{
		while (st->args[i][j])
		{
			if (st->args[i][j] == '"')
				j++;
			ft_putchar(st->args[i][j]);
			j++;
		}
		i++;
		j = 0;
		ft_putchar(' ');
	}
	st->b_trig = 1;
	ft_putchar('\n');
}