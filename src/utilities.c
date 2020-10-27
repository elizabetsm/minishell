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

	tmp = ft_strjoin(path, "/");
	put = ft_strjoin(tmp, command);
	return (put);
}

void		delete_splitted_line(char ***splitted_line)
{
	int i;

	i = 0;
	while ((*splitted_line)[i])
	{
		free((*splitted_line)[i]);
		(*splitted_line)[i] = NULL;
		i++;
	}
	free(*splitted_line);
	splitted_line = NULL;
}

void	ft_free(t_struct *st)
{
	int i;

	i = 0;
	st->b_trig = 0;
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
