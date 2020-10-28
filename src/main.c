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
		if (is_space(st->inp[i]) == 1)
		{
			i++;
			continue;
		}
		else
		{
			st->args[j] = (char *)ft_memalloc(sizeof(char) * 20);
			while (st->inp[i] != ' ' && st->inp[i] != '\0' &&
			st->inp[i] != '	')
				st->args[j][k++] = st->inp[i++];
			st->args[j][k] = '\0';
			j++;
			k = 0;
		}
		if (st->inp[i] != '\0')
			i++;
	}
	st->args[j] = NULL;
}

void	input(t_struct *st)
{
	char	buf;
	int		i;

	st->inp = (char *)malloc(sizeof(char *) * 100);
	i = 0;
	while (read(0, &buf, 1) && buf != '\n')
	{
		st->inp[i] = buf;
		i++;
	}
	st->inp[i] = '\0';
	if (st->inp[0] != '\0')
		parse_imp(st);
}

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
	st->paths = ft_strsplit(p, ':');
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

int		exec(t_struct *st, char *path)
{
	pid_t	pid;
	int		trig;
	char	*paths;
	int		i;

	i = 0;
	trig = 1;
	paths = ft_strcpy(st->args[0], path);
	st->args[0] = paths;
	if ((pid = fork()) == 0)
	{
		i = execve(st->args[0], st->args, NULL);
		if (i < 0)
		{
			ft_putstr(st->args[0]);
			ft_putstr(" : command not found\n");
		}
	}
	else
		wait(&pid);
	return (trig);
}

void	execute(t_struct *st)
{
	int			i;
	int			trig;
	char		*path;
	char		*tmp;

	i = 0;
	trig = 0;
	get_paths(st, "PATH");
	tmp = ft_strdup("");
	path = ft_strjoin(&tmp, &st->args[0], 1, 0);
	while (st->paths[i++])
	{
		if (access(path, X_OK) != -1)
			trig = exec(st, path);
		ft_memdel((void *)&path);
		path = pathjoin(st->paths[i], st->args[0]);
	}
	ft_memdel((void *)&path);
	if (trig == 0)
	{
		ft_putstr(st->args[0]);
		ft_putstr(" : command not found\n");
	}
}

void	check_built(t_struct *st)
{
	if (ft_strcmp(st->args[0], "echo") == 0)
		echo_builtin(st);
	else if (ft_strcmp(st->args[0], "cd") == 0)
		cd_builtin(st);
	else if (ft_strcmp(st->args[0], "setenv") == 0)
		setenv_builtin(st);
	else if (ft_strcmp(st->args[0], "unsetenv") == 0)
		unsetenv_builtin(st);
	else if (ft_strcmp(st->args[0], "env") == 0)
		env_builtin(st);
	else if (ft_strcmp(st->args[0], "exit") == 0)
	{
		ft_strdel(&st->homedir);
		ft_strdel(&st->dir);
		delete_splitted_line(&(st->env));
		ft_free(st);
		free(st);
		exit(1);
	}
}

void	copy_env(t_struct *st, char **env)
{
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	k = -1;
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

int		main(int argc, char **argv, char **env)
{
	t_struct	*st;
	char		*dir;

	st = (t_struct	*)ft_memalloc(sizeof(t_struct));
	init_st(st);
	copy_env(st, env);
	while (1)
	{
		ft_putstr("\033[1;34m");
		print_dir(st->dir = getcwd(dir, sizeof(dir)));
		ft_putstr("\033[0m");
		input(st);
		if (st->inp[0] != '\0' && st->args[0] != NULL)
		{
			check_built(st);
			if (st->b_trig == 0)
			{
				execute(st);
				delete_splitted_line(&(st->paths));
			}
			ft_free(st);
		}
		ft_strdel(&st->dir);
	}
}
