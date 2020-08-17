#ifndef MINISHELL_H
# define MINISHELL_H

 #include "../libft/libft.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

typedef struct	s_struct {
	char		*inp;
	char		**env;
	char		*dir;
	char 		**args;
}				t_struct;

// void print(char *name);
//void			parce(t_struct *mini);
//void			print_prompt(char *dir);
//void			handler(t_struct *mini, char **env);
//char			*ft_strjoin(char const *s1, char const *s2);
//void			vvod(t_struct *mini);
//void			ft_putchar(char c);
//void			ft_putstr(char *str);

#endif