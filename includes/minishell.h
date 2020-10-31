/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 16:07:37 by efleta            #+#    #+#             */
/*   Updated: 2020/10/30 16:07:39 by efleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <dirent.h>

typedef struct	s_struct {
	char		*inp;
	char		**args;
	int			b_trig;
	char		**paths;
	char		**env;
	char		*dir;
	char		*homedir;
	int			h_trig;
}				t_struct;

void			echo_builtin(t_struct *st);
void			check_built(t_struct *st);
void			execute(t_struct *st);
void			input(t_struct *st);
void			cd_builtin(t_struct *st);
void			env_builtin(t_struct *st);
void			setenv_builtin(t_struct *st);
void			unsetenv_builtin(t_struct *st);
int				exec(t_struct *st, char *path);
char			*pathjoin(char *path, char *command);
void			ft_free(t_struct *st);
void			print_dir(char *path);
void			init_st(t_struct *st, char **argv);
void			delete_splitted_line(char ***splitted_line);
void			get_paths(t_struct *st, char *word);
void			parse_input(t_struct *st);
void			copy_env(t_struct *st, char **env, int argc);
char			*ft_realloc(char *str, int new_size);

#endif
