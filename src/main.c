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

char	**get_path(char **env, char *path)
{
	int		i;
	int		j;
	int		a;
	char	*put;
	char	**puti;

	i = 0;
	j = 0;
	a = 0;
	while (env[i] && path[j])
	{
		if (env[i][0] == path[j])
		{
			while (path[j])
			{
				if (env[i][j] == path[j])
					a++;
				j++;
			}
			if (path[a] == '\0')
			{
				a = 0;
				j = 0;
				while (env[i][a] != '=')
					a++;
				a++;
				put = (char *)malloc(sizeof(char) * 20);
				while (env[i][a])
				{
					put[j] = env[i][a];
					j++;
					a++;
				}
				puti = ft_strsplit(put, ':');
				return (puti);
			}
			else
			{
				j = 0;
				a = 0;
			}

		}
		i++;
	}
	return NULL;
}

char	*pathjoin(char *path, char *command)
{
	char	*tmp;
	char	*put;

	tmp = ft_strjoin(path, "/");
	put = ft_strjoin(tmp, command);
	return (put);
}

void	execute(t_struct *st, char **env)
{
	int			i;
	pid_t		pid;
	char 		**paths;
	char		*path;
	struct stat	*buf;

	i = 0;
	paths = get_path(env, "PATH");
	while (paths[i])
	{
		path = pathjoin(paths[i], st->args[0]);
		if (stat(path, buf) == 0)
		{
//			ft_memdel((void *)st->args[0]);
//			st->args[0] = ft_memalloc(ft_strlen(path) + 1);
			st->args[0] = ft_strcpy(st->args[0], path);
			ft_putstr(st->args[0]);
			if ((pid = fork()) == 0)
			{
//				if (strcmp(st->args[0], "exit"))
//					kill(pid, SIGQUIT);
				i = execve(st->args[0], st->args, env);
				if (i < 0)
				{
					ft_putstr(st->args[0]);
					ft_putstr(" : command not found\n");
				}
			}
			else
			{
//				if (strcmp(st->args[0], "exit"))
//					kill(pid, SIGQUIT);
				wait(&pid);
			}

		}
		i++;
	}
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
//		kill
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

void 	copy_env(t_struct *st, char **env)
{
	int i;
	int j;

	i = 0;
	j = 0;
	st->env = ft_memalloc(20);
	while (env[i])
	{
		st->env[i] = ft_memalloc(ft_strlen(env[i]));
		while (env[i][j])
		{
			st->env[i][j] = env[i][j];
			j++;
		}
		j = 0;
		i++;
	}
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
		copy_env(st, env);
		input(st);
		check_built(st, env);
		if (st->b_trig == 0)
			execute(st, env);
		ft_free(st);
	}
}
