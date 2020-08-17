#include "../includes/minishell.h"

void	input(t_struct *st)
{
	char buf;
	int i;

	st->inp = (char *)malloc(sizeof(char) * 15);

	i = 0;
	while(read(0, &buf, 1) && buf != '\n')
	{
		st->inp[i] = buf;
		i++;
	}
	st->inp[i] = '\0';
	st->args = ft_strsplit(st->inp, ' ');
	i = 0;
	while (st->args[i])
		i++;
	st->args[i] = NULL;

}

void handler(t_struct *st, char **env)
{
	int i;
	pid_t pid;

	pid = fork();

	if (pid == 0)
	{
		i = execve(st->args[0],st->args, env);
		if (i < 0)
		{
			ft_putstr(st->args[0]);
			ft_putstr(" : command not found\n");
		}
	}
	else
		wait(&pid);
}

int		main(int argc, char **argv, char **env)
{
	t_struct *st;

	st = malloc(sizeof(t_struct));
	while (1)
	{
		ft_putstr("\033[1;34m");
		ft_putstr("pishi suda -> ");
		ft_putstr("\033[0m");
		input(st);
		handler(st, env);
	}
}