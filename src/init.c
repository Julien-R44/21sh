/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: y0ja <y0ja@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/26 02:34:59 by jripoute          #+#    #+#             */
/*   Updated: 2015/05/11 04:43:53 by y0ja             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

char	**get_path_dirs(char **env)
{
	char	**array;
	char	*tmp;
	int		i;
	int		len;

	i = 0;
	tmp = get_env(env, "PATH=");
	if (tmp == NULL)
		return (NULL);
	array = ft_strsplit(tmp, ':');
	while (array[i])
	{
		len = ft_strlen(array[i]);
		if (array[i][len - 1] != '/')
		{
			tmp = ft_strjoin(array[i], "/");
			free(array[i]);
			array[i] = tmp;
		}
		i++;
	}
	return (array);
}

static void		init_path_dirs(t_all *all)
{
	if (all->env.path_dir)
		ft_2dchardel(&all->env.path_dir);
	all->env.path_dir = get_path_dirs(all->env.env);
}

void		crash_handler(int sig)
{
	printf("\n");
	if (sig == SIGINT || sig == SIGCONT)
		display_prompt(f_all(NULL));
	else
		exit(0);
}

static void		signals_handlers(void)
{
	signal(SIGINT, crash_handler);
	// signal(SIGSEGV, crash_handler);
	signal(SIGCONT, crash_handler);
}

void			init_termcap(t_all *all)
{
	char	*termtype;
	int		ret;

	all->term.tty = 1;
	if (!(termtype = getenv("TERM")))
		ft_error(all, NOTERMENV);
	ret = tgetent(NULL, termtype);
	if (ret < 0)
		ft_error(all, TERMINFODB);
	if (ret == 0)
		ft_error(all, TERMNOTDEF);
	if (tcgetattr(all->term.tty, &all->term.term) == -1)
		ft_error(all, GETATTR);
	if (tcgetattr(all->term.tty, &all->term.oldterm) == -1)
		ft_error(all, GETATTR);
	all->term.term.c_lflag &= ~(ICANON | ECHO);
	all->term.term.c_cc[VMIN] = 1;
	all->term.term.c_cc[VTIME] = 0;
	if (tcsetattr(all->term.tty, TCSADRAIN, &all->term.term) == -1)
		ft_error(all, GETATTR);
}


void			init_shell(t_all *all, char **env)
{
	signals_handlers();
	init_termcap(all);
	all->cmds = NULL;
	all->cmd.args = NULL;
	all->cmd.path = NULL;
	all->env.path_dir = NULL;
	all->env.env = ft_2dchardup(env);
	init_path_dirs(all);
}
