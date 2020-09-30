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
//	while (st->args[i])
//		i++;
//	st->args[i] = ft_strdup(st->path);
//	st->args[i] = NULL;
}

void get_paths(t_struct *st, char *word)
{
	int i;
	int j;
	int k;
	char *p;

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
//				int a = -1;
//				while (st->paths[++a])
//				{
//					ft_putstr(st->paths[a]);
//
//					ft_putchar('\n');
//				}
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
	pid_t		pid;
	char 		*paths;
	char		*path;
	struct stat	*buf;

	i = 0;
	get_paths(st, "PATH");
	while (st->paths[i])
	{
		buf = ft_memalloc(sizeof(&buf));
		path = pathjoin(st->paths[i], st->args[0]);
		if (access(path, X_OK) != -1)
		{
			//ft_memdel((void *)st->args[0]);
			paths = ft_strcpy(st->args[0], path);
			st->args[0] = paths;
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
		free((void *)buf);
		}
		i++;
	}
}

void	check_built(t_struct *st, char **env)
{
	if (ft_strcmp(st->args[0], "echo") == 0)
		echo_builtin(st);
	else if (ft_strcmp(st->args[0], "cd") == 0)
		cd_builtin(st, env);
	else if (strcmp(st->args[0], "setenv") == 0)
		setenv_builtin(st);
//	else if (strcmp(st->args[0], "unsetenv"))
//		st->com_trig = 'u';
	else if (ft_strcmp(st->args[0], "env") == 0)
		env_builtin(st);
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

void 	copy_env(t_struct *st, char **env) //какой то мусор в начале
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
	st->env[i] = NULL;
}

int		main(int argc, char **argv, char **env)
{
	t_struct	*st;

	st = malloc(sizeof(t_struct));
	st->b_trig = 0;
	char dir[PATH_MAX];
//	st->path = getcwd(dir, sizeof(dir));
	copy_env(st, env);
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
