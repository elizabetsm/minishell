/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 14:25:12 by efleta            #+#    #+#             */
/*   Updated: 2020/10/24 16:24:04 by efleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"



void	parse_imp(t_struct *st)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;

	st->args = (char **)ft_memalloc(sizeof(char *) * 10);
	while (st->inp[i])
	{
		if (st->inp[i] == ' ')
		{
			i++;
			continue;
		}
		else if (st->inp[i] == '	')
		{
			i++;
			continue;
		}
		else
		{
			st->args[j] = (char *)ft_memalloc(sizeof(char) * 20);
			while (st->inp[i] != ' ' && st->inp[i] != '\0' && st->inp[i] != '	')
			{

				st->args[j][k++] = st->inp[i++];
			}
			st->args[j][k] = '\0';
			j++;
			k = 0;
		}
		i++;
	}
	st->args[j] = NULL;
}

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
	if (st->inp[0] != '\0')
	{

		st->inp[i] = '\0';
		parse_imp(st);
//		st->args = ft_strsplit(st->inp, ' ');
//		i = 0;
//		while (st->args[i])
//		{
//			printf("\n %d = .%s.\n", i, st->args[i]);
//			i++;
//		}
//		ft_memdel((void **)st->inp);
	}
}

void	get_paths(t_struct *st, char *word)
{
	int		i;
	int		j;
	int		k;
	char	*p;

	i = 0;
	j = 0;
	k = 0;
	while (st->env[i])
	{
		if (st->env[i][0] == word[0])
		{
			while (word[j])
			{
				if (word[j] == st->env[i][j])
					k++;
				j++;
			}
			if (word[j] == '\0')
			{
				j = 0;
				k = 0;
				while (st->env[i][j] != '=')
					j++;
				p = ft_memalloc(sizeof(char *) * ft_strlen(st->env[i]) - k);
				while (st->env[i][j])
				{
					p[k] = st->env[i][j];
					k++;
					j++;
				}
				st->paths = ft_strsplit(p, ':');
				return ;
			}
			else
			{
				k = 0;
				j = 0;
			}
		}
		i++;
	}
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
	int 		trig;
	pid_t		pid;
	char		*paths;
	char		*path;
//	struct stat	*buf;

	i = 0;
	trig = 0;
	get_paths(st, "PATH");
	path = ft_strjoin("", st->args[0]);
	while (st->paths[i])
	{
//		buf = ft_memalloc(sizeof(&buf));
//		if (access(path, X_OK) == -1)

		if (access(path, X_OK) != -1)
		{
			trig = 1;
			paths = ft_strcpy(st->args[0], path);
			st->args[0] = paths;
			if ((pid = fork()) == 0)
			{
//
				i = execve(st->args[0], st->args, env);
				if (i < 0)
				{
//					trig = 0;
					ft_putstr(st->args[0]);
					ft_putstr(" : command not found\n");
				}
			}
			else
				wait(&pid);
		}
		path = pathjoin(st->paths[i], st->args[0]);
		i++;
	}
	if (trig == 0)
	{
		ft_putstr(st->args[0]);
		ft_putstr(" : command not found\n");
	}
}

void	check_built(t_struct *st, char **env)
{
	if (ft_strcmp(st->args[0], "echo") == 0)
		echo_builtin(st);
	else if (ft_strcmp(st->args[0], "cd") == 0)
		cd_builtin(st, env);
	else if (ft_strcmp(st->args[0], "setenv") == 0)
		setenv_builtin(st);
//	else if (ft_strcmp(st->args[0], "unsetenv"))
//		st->com_trig = 'u';
	else if (ft_strcmp(st->args[0], "env") == 0)
		env_builtin(st);
	else if (ft_strcmp(st->args[0], "exit") == 0)
		exit(1);
}

void	ft_free(t_struct *st)
{
	int i;

	i = 0;

	st->b_trig = 0;
}

void	copy_env(t_struct *st, char **env)
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
		st->env[i][j] = '\0';
		j = 0;
		i++;
	}
	st->env[i] = NULL;
}

void	print_dir(char *path)
{
	size_t i;

	i = ft_strlen(path);
	while (path[i] != '/')
		i--;
	ft_putstr("~/");
	while (path[i++])
		ft_putchar(path[i]);
	ft_putchar(' ');
}

void	init_st(t_struct *st)
{
	st->inp = NULL;
	st->b_trig = 0;
	st->paths = NULL;
	st->env = NULL;
	st->args = NULL;
}

int		main(int argc, char **argv, char **env)
{
	t_struct	*st;
	char		*dir;

	st = ft_memalloc(sizeof(t_struct));

	init_st(st);
	copy_env(st, env);
	while (1)
	{
		ft_putstr("\033[1;34m");
		print_dir(st->dir = getcwd(dir, sizeof(dir)));
		ft_putstr("\033[0m");
		ft_putstr(st->env[0]);
		input(st);
		if (st->inp[0] != '\0' && st->args[0] != NULL)
		{
			check_built(st, env);
			if (st->b_trig == 0)
				execute(st, env);
			ft_free(st);
		}

	}
}
