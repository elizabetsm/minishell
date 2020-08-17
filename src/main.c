/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 14:25:12 by efleta            #+#    #+#             */
/*   Updated: 2020/08/17 14:25:15 by efleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	input(t_struct *st)
{
	char	buf;
	int		i;

	st->inp = (char *)malloc(sizeof(char) * 15);
	i = 0;
	while (read(0, &buf, 1) && buf != '\n')
	{
		st->inp[i] = buf;
		i++;
	}
	st->inp[i] = '\0';
	st->args = ft_strsplit(st->inp, ' ');
	i = 0;
	while (st->args[i])
		i++;
//	st->args[i] = ft_strdup(st->path);
	st->args[i] = NULL;
}

void	execute(t_struct *st, char **env)
{
	int		i;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		i = execve(st->args[0], st->args, env);
		if (i < 0)
		{
			ft_putstr(st->args[0]);
			ft_putstr(" : command not found\n");
		}
	}
	else
		wait(&pid);
}

void	check_built(t_struct *st, char **env)
{
	if (strcmp(st->args[0], "echo") == 0)
		echo_builtin(st);
	else if (strcmp(st->args[0], "cd") == 0)
		cd_builtin(st, env);
//	else if (strcmp(st->args[0], "setenv"))
//		st->com_trig = 's';
//	else if (strcmp(st->args[0], "unsetenv"))
//		st->com_trig = 'u';
//	else if (strcmp(st->args[0], "env"))
//		st->com_trig = 'e';
//	else if (strcmp(st->args[0], "exit"))
//		st->com_trig = 'e';
}


void ft_free(t_struct *st)
{
	int i;

	i = 0;
//	ft_memdel((void *)st->inp);
	st->b_trig = 0;
//	while (st->args[i])
//	{
//		ft_memdel((void *)st->args[i]);
//		i++;
//	}
}



int		main(int argc, char **argv, char **env)
{
	t_struct	*st;

	st = malloc(sizeof(t_struct));
	st->b_trig = 0;
	char dir[PATH_MAX];
	st->path = getcwd(dir, sizeof(dir));

	while (1)
	{
		ft_putstr("\033[1;34m");
		ft_putstr("pishi suda -> ");
		ft_putstr("\033[0m");
		input(st);
		check_built(st, env);
		if (st->b_trig == 0)
			execute(st, env);
		ft_free(st);
	}
}
