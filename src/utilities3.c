/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 17:43:09 by efleta            #+#    #+#             */
/*   Updated: 2020/10/30 17:43:10 by efleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		is_space(char c)
{
	if (c == ' ' || c == '	')
		return (1);
	return (0);
}

char	*ft_realloc(char *str, int new_size)
{
	char *newstr;

	newstr = ft_memalloc(sizeof(char) * (ft_strlen(str) + new_size + 1));
	ft_strcpy(newstr, str);
	ft_memdel((void **)&str);
	return (newstr);
}

void	copy_env(t_struct *st, char **env, int argc)
{
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	k = -1;
	argc = 1;
	while (env[++k])
		;
	st->env = (char **)ft_memalloc(sizeof(char *) * (k + 1));
	while (env[i])
	{
		st->env[i] = (char *)ft_memalloc(sizeof(char *) *
				ft_strlen(env[i]) + 10 + 1);
		while (env[i][j])
		{
			st->env[i][j] = env[i][j];
			j++;
		}
		st->env[i][j] = '\0';
		j = 0;
		i++;
	}
	st->env[i] = NULL;
}
