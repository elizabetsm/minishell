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
	char		*inp; /*здесь хранится ввод*/
	char		**args; /*здесь хранится строка после вводаБ разделенная по словам*/
	int			b_trig;
	char 		*path;
}				t_struct;

void	echo_builtin(t_struct *st);
void	check_built(t_struct *st, char ** env);
void	execute(t_struct *st, char **env);
void	input(t_struct *st);
void	cd_builtin(t_struct *st, char **env);
#endif