#include "../includes/minishell.h"

int		is_space(char c)
{
	if (c == ' ' || c == '	')
		return (1);
	return (0);
}

char	*pathjoin(char *path, char *command)
{
	char	*tmp;
	char	*put;
	char *t;

	t = ft_strdup("/");
	tmp = ft_strjoin(&path, &t, 0, 1);
	put = ft_strjoin(&tmp, &command, 1, 0);
	return (put);
}

void		delete_splitted_line(char ***splitted_line)
{
	int i;
	char **tmp;

	i = 0;
	tmp = *splitted_line;
	while (tmp && tmp[i])
	{
		ft_strdel(&tmp[i]);
		tmp[i] = NULL;
		i++;
	}
	if (tmp)
		free(tmp);
	tmp = NULL;
}

void	ft_free(t_struct *st)
{
	int i;

	i = 0;
	st->b_trig = 0;
	ft_strdel(&st->inp);
	delete_splitted_line(&(st->args));
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
	st->homedir = NULL;
	st->h_trig = 0;
}
