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

void unsetenv_builtin(t_struct *st)
{
	char *arg;
	int i;
	int j;
	int k;
	char **newenv;

	i = 0;
	j = 0;
	k = 0;
	arg = st->args[1];
	while (st->env[i])
	{
		if (st->env[i][0] == arg[0])
		{
			while (arg[j])
			{
				if (arg[j] == st->env[i][j])
					k++;
				j++;
			}
			if (arg[k] == '\0')
				i = i;
			k = 0;
			j = 0;
		}
		newenv[i] = ft_memalloc(sizeof(char *) * ft_strlen(st->env[i]) + 1);
		ft_strcpy(newenv[i], st->env[i]);
		ft_memdel((void **)st->env[i]);
		i++;
	}
	st->env = newenv;
}