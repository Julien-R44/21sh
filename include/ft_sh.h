/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sh.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <lubaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/25 02:22:43 by jripoute          #+#    #+#             */
/*   Updated: 2015/05/12 12:58:59 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SH_H
# define FT_SH_H

# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>
# include <fcntl.h>
# include <time.h>
# include <curses.h>
# include <termios.h>

# include <stdio.h>

# include "libft.h"
# include "colors.h"
# include <term.h>

# define K_ISECHAP	(buf[0] == 27 && (!buf[1] && !buf[2]))
# define K_ISTOP	(buf[0] == 27 && buf[1] == 91 && buf[2] == 65)
# define K_ISBOT	(buf[0] == 27 && buf[1] == 91 && buf[2] == 66)
# define K_ISRIGHT	(buf[0] == 27 && buf[1] == 91 && buf[2] == 67)
# define K_ISLEFT	(buf[0] == 27 && buf[1] == 91 && buf[2] == 68)
# define K_ISSPACE	(buf[0] == 32 && (!buf[1] && !buf[2]))
# define K_ISSUPR	(buf[0] == 27 && buf[1] == 91 && buf[2] == 51)
# define K_ISBACKS	(buf[0] == 127 && !(buf[1] && !(buf[2])))
# define K_IS_ENTER	(buf[0] == 10 && !(buf[1] && !(buf[2])))
# define K_CTRLD	(buf[0] == 4)

# define READ_END 0
# define WRITE_END 1

# define BUFF_SIZ 2096
// mkdir test ; cd test ; ls -a ; ls | cat | wc -c > tutu ; cat tutu

typedef enum		e_error
{
	NOTERMENV,
	TERMINFODB,
	TERMNOTDEF,
	GETATTR,
	NO_ENV2SET,
	NO_CMD_FOUND,
	NO_ENV2UNSET,
	NO_SUCH_FILE,
	SYSCALL_FAIL,
	PERM_DENIED,
	OPENDIR_FAIL,
}					t_error;

typedef struct		s_cmd
{
	char			*path;
	char			**args;
	char			**to_pipe;
}					t_cmd;

typedef struct		s_env
{
	char			**env;
	char			**path_dir;
	char			**cmd2exec;
}					t_env;

typedef struct		s_term
{
	int				tty;
	struct termios	term;
	struct termios	oldterm;
}					t_term;

typedef struct		s_all
{
	t_cmd			cmd;
	t_dlist			*cmds;
	t_env			env;
	t_term			term;
}					t_all;

typedef struct dirent	t_dirent;

t_all			*f_all(t_all *all);

/*
** init.c
*/
void			init_shell(t_all *all, char **env);
char			**get_path_dirs(char **env);

/*
** parser_input.c
*/
int				parse_cmd(t_all *all, char *cmd);
void			parse_args(t_all *all);
char			**scan_for_input(t_all *all);

/*
** split_parser.c
*/
char			**split_quotes(char **cmd);
char			**split_to_use(char *cmd);

/*
** parse_var.c
*/
char			*replace_var(t_all *all, char *cmd);
char			*matching_var(t_all *all, char *cmd, int i, int *index_end_var);

/*
** search_bin.c
*/
int				bin_is_here(t_all *all, char *bin, char *path_dir);
void			search_binary_in_path_dirs(t_all *all, char *binf);

/*
** builtin.c
*/
int				cmd_is_builtin(t_all *all);

/*
** builtin_env.c
*/
void			unset_env(t_all *all, char *var);
int				add_new_env(t_env *env, char *newenv);
void			set_env(t_all *all, char *var, char *value);

/*
** process.c
*/
void			exec_piped_process(t_all *all);
void			exec_new_process(t_all *all, char *file_redir, int append);
pid_t			secure_fork(t_all *all);

/*
** display.c
*/
void			display_prompt(t_all *all);

/*
** error.c
*/
void			free_all(t_all *all);
void			exit_normal(t_all *all, int exit_ret);
void			error_no_quit(int er, t_all *all);
int				get_error(t_all *all, int er, void *data);
void			error_quit(t_all *all, int er);
void			ft_error(t_all *all, int er);
void			free_cmd(t_cmd *cmd);

/*
** misc.c
*/
char			*get_env(char **env, char *var);
char			**get_env_addr(char **env, char *var);
void			del_tabulation(char *c);
void			reload_path_dirs(t_all *all);
int				is_not_escaped(char c, char c2, char c_prev);
void			tgetstr_cpb(char *cpb);

#endif
