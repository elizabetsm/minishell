#ifndef MINISHELL_H
# define MINISHELL_H

 #include "../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <dirent.h>

typedef struct	s_struct {
	char		*inp; /*здесь хранится ввод*/
	char		**args; /*здесь хранится строка после вводаБ разделенная по словам*/
	int			b_trig;
	char 		**paths;
	char 		**env;
	char 		*dir;
	char 		*homedir;
	int 		h_trig;
}				t_struct;

void	echo_builtin(t_struct *st);
void	check_built(t_struct *st);
void	execute(t_struct *st);
void	input(t_struct *st);
void	cd_builtin(t_struct *st);
void	env_builtin(t_struct *st);
void	setenv_builtin(t_struct *st);
void	unsetenv_builtin(t_struct *st);
int		exec(t_struct *st, char *path);
int		is_space(char c);
char	*pathjoin(char *path, char *command);
void	ft_free(t_struct *st);
void	print_dir(char *path);
void	init_st(t_struct *st);

#endif