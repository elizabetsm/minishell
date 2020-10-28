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

void env_builtin(t_struct *st)
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


void setenv_builtin(t_struct *st)
{
	int i;

	i = 0;
	st->b_trig = 1;
	while(st->env[i])
		i++;
	st->env[i] = ft_memalloc(sizeof(char *) * ft_strlen(st->args[1]));
	char *tmp;
	tmp = ft_memalloc(sizeof(char *) * ft_strlen(st->args[1]));
	st->env[i] = ft_strcpy(tmp, st->args[1]);
	i++;
	st->env[i] = NULL;
}

int compare_before_sign_equally(const char *str, const char *compared)
{
	int i = 0;

	while (str[i] == compared[i])
		i++;
	if (str[i] == '=' && !compared[i])
		return 1;
	return 0;
}

int get_new_env_size(char **env, char *word)
{
	int i = -1;
	int is_word_exist = 0;

	while(env[++i])
	{
		if (compare_before_sign_equally(env[i], word))
			is_word_exist = 1;
	}
	if (is_word_exist)
		return i - 1;
	return 0;
}

void unsetenv_builtin(t_struct *st)
{
	int i;
	int j;
	char **newenv;

	st->b_trig = 1;
	if (!st->args[1])
		return;
	int newenv_size;
	if (!(newenv_size = get_new_env_size(st->env, st->args[1])))
		return;
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

//	i = -1;
//	while (newenv[++i])
//		printf("%s\n", newenv[i]);
//	printf("\nAAAAAAAAAAAA\n");

	delete_splitted_line(&(st->env));
	st->env = newenv;
//	delete_splitted_line(&(newenv));
}
