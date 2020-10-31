/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 22:27:45 by efleta            #+#    #+#             */
/*   Updated: 2020/10/28 22:27:47 by efleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	env_builtin(t_struct *st)
{
	int i;

	i = -1;
	while (st->env[++i])
	{
		ft_putstr(st->env[i]);
		ft_putchar('\n');
	}
	st->b_trig = 1;
}

void	setenv_builtin(t_struct *st)
{
	char	**newenv;
	int		i;
	int		k;

	i = 0;
	k = -1;
	st->b_trig = 1;
	if (!st->args[1])
		return ;
	while (st->env[++k])
		;
	newenv = (char **)ft_memalloc(sizeof(char *) * (k + 2));
	while (st->env[i])
	{
		newenv[i] = (char *)ft_memalloc(sizeof(char) *
				(ft_strlen(st->env[i]) + 1));
		ft_strcpy(newenv[i], st->env[i]);
		i++;
	}
	newenv[i] = (char *)ft_memalloc(sizeof(char) *
			ft_strlen(st->args[1]) + 1);
	ft_strcpy(newenv[i], st->args[1]);
	newenv[i + 1] = NULL;
	delete_splitted_line(&(st->env));
	st->env = newenv;
}

int		compare_before_sign_equally(const char *str, const char *compared)
{
	int i;

	i = 0;
	while (str[i] && compared[i] && str[i] == compared[i])
		i++;
	if (str[i] == '=' && compared[i] == '\0')
		return (1);
	return (0);
}

int		get_new_env_size(char **env, char *word)
{
	int i;
	int is_word_exist;

	i = 0;
	is_word_exist = 0;
	while (env[i])
	{
		if (compare_before_sign_equally(env[i], word))
			is_word_exist = 1;
		if (env[i] != NULL)
			i++;
	}
	if (is_word_exist)
		return (i - 1);
	return (0);
}

void	unsetenv_builtin(t_struct *st)
{
	int		i;
	int		j;
	char	**newenv;
	int		newenv_size;

	st->b_trig = 1;
	if (!st->args[1])
		return ;
	if (!(newenv_size = get_new_env_size(st->env, st->args[1])))
		return ;
	newenv = ft_memalloc(sizeof(char *) * (newenv_size + 1));
	j = 0;
	i = -1;
	while (st->env[++i])
	{
		if (!compare_before_sign_equally(st->env[i], st->args[1]))
		{
			newenv[j] = ft_memalloc(sizeof(char) * (ft_strlen(st->env[i]) + 1));
			ft_strcpy(newenv[j], st->env[i]);
			j++;
		}
	}
	delete_splitted_line(&(st->env));
	st->env = newenv;
}
