/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elizaveta <elizaveta@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 23:01:10 by elizaveta         #+#    #+#             */
/*   Updated: 2020/06/17 23:02:29 by elizaveta        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_prompt(char *dir)
{
	int i;

	i = 0;
    ft_putstr("\033[36m");
	while(dir[i] != '\0')
		i++;
	while(dir[i] != '/')
		i--;
	ft_putstr("~");
	while(dir[i] != '\0')
	{
		ft_putchar(dir[i]);
		i++;
	}
    ft_putstr("\033[0m");
	ft_putstr(" ");
}