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

char	*ft_realloc(char *str, int new_size)
{
	char *newstr;

	newstr = ft_memalloc(sizeof(char) * (ft_strlen(str) + new_size + 1));
	ft_strcpy(newstr, str);
	ft_memdel((void **)&str);
	return (newstr);
}

void	input(t_struct *st)
{
	char	buf;
	int		i;

	if (!(st->inp = ft_memalloc(sizeof(char) * 2)))
		return ;
	i = 0;
	while (read(0, &buf, 1) && buf != '\n')
	{
		if (i > 0)
			st->inp = ft_realloc(st->inp, sizeof(buf));
		st->inp[i] = buf;

		i++;
	}
	st->inp[i] = '\0';
	if (st->inp[0] != '\0')
		parse_input(st);
	else
	{
		ft_memdel((void **)&st->inp);
		st->inp = NULL;
	}
}

int		exec(t_struct *st, char *path)
{
	pid_t	pid;
	int		trig;
	int		i;

	trig = 1;
	free(st->args[0]);
	st->args[0] = ft_strdup(path);
	if ((pid = fork()) == 0)
	{
		i = execve(st->args[0], st->args, st->env);
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

int		main(int argc, char **argv, char **env)
{
	t_struct	*st;
	char		*dir;

	dir = NULL;
	st = (t_struct	*)ft_memalloc(sizeof(t_struct));
	init_st(st, argv);
	copy_env(st, env, argc);
	while (1)
	{
		ft_putstr("\033[1;34m");
		print_dir(st->dir = getcwd(dir, sizeof(dir)));
		ft_putstr("\033[0m");
		input(st);
		if (st->inp != NULL && st->args != NULL)
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
