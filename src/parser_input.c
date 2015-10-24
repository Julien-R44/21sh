/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <lubaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/25 02:22:43 by jripoute          #+#    #+#             */
/*   Updated: 2015/05/12 11:04:20 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static char		*replace_tilde(t_all *all, char *cmd)
{
	char	*newstr;
	char	*home;

	newstr = cmd;
	if (cmd[0] == '~')
	{
		home = get_env(all->env.env, "HOME=");
		newstr = ft_strjoin(home, &cmd[1]);
		free(cmd);
	}
	return (newstr);
}

void			parse_args(t_all *all)
{
	int i;

	i = 0;
	while (all->cmd.args[i])
	{
		all->cmd.args[i] = replace_tilde(all, all->cmd.args[i]);
		all->cmd.args[i] = replace_var(all, all->cmd.args[i]);
		i++;
	}
}

char		*get_input_tc(t_all *all)
{
	char	buf[3] = {0};
	char	*buf2;
	int		i = 0;

	buf2 = ft_strnew(BUFF_SIZE + 1);
	while (read(1, buf, 3) > 0)
	{
		// printf("%d %d %d\n", buf[0],buf[1],buf[2] );
		if (K_CTRLD)
			exit_normal(all, 42);
		else if (K_IS_ENTER)
			break ;
		else if (K_ISBACKS)
		{
			i--;
			buf2[i] = 0;
		}
		else if (buf[0] && !(buf[1]) && !(buf[2]))
		{
			ft_putchar_fd(buf[0], 2);
			buf2[i] = buf[0];
			i++;
		}
		buf2[i] = 0;
		ft_bzero(&buf, 3);
	}
	ft_putchar('\n');
	return (buf2);
}

char			**scan_for_input(t_all *all)
{
	char	*cmd;
	char	**cmd2exec;

	cmd = NULL;
	cmd = get_input_tc(all);
	ft_striter(cmd, del_tabulation);
	cmd2exec = ft_strsplit(cmd, ';');
	free(cmd);
	return (cmd2exec);
}

int				parse_cmd(t_all *all, char *cmd)
{
	all->cmd.to_pipe = ft_strsplit(cmd, '|');
	// parse_args(all);
	free(cmd);
	return (1);
}
