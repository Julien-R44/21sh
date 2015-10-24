/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: y0ja <y0ja@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/25 02:22:43 by jripoute          #+#    #+#             */
/*   Updated: 2015/05/11 03:37:50 by y0ja             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static void		change_directory(t_all *all)
{
	char	cwd[1024];
	char	*go_to;

	if (!all->cmd.args[1])
		go_to = get_env(all->env.env, "HOME=");
	else
		go_to = all->cmd.args[1];
	if (chdir(go_to) == -1)
	{
		if (access(go_to, F_OK) != 0)
			error_no_quit(NO_SUCH_FILE, all);
		else if (access(go_to, R_OK | W_OK | X_OK) != 0)
			error_no_quit(PERM_DENIED, all);
	}
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		ft_error(all, SYSCALL_FAIL);
	set_env(all, "OLDPWD", get_env(all->env.env, "PWD="));
	set_env(all, "PWD", cwd);
}

static void		display_env(t_all *all)
{
	int i;

	i = 0;
	while (all->env.env[i])
	{
		ft_putendl(all->env.env[i]);
		i++;
	}
}

static void		built_echo(t_cmd *cmd)
{
	int i;
	int j;

	j = 0;
	i = 1;
	while (cmd->args[i])
	{
		while (cmd->args[i][j])
		{
			if (cmd->args[i][j] == '\\' && cmd->args[i][j + 1] == 'n')
			{
				ft_putchar('\n');
				j += 2;
			}
			ft_putchar(cmd->args[i][j]);
			j++;
		}
		ft_putchar(' ');
		j = 0;
		i++;
	}
	ft_putchar('\n');
}

int		cmd_is_builtin(t_all *all)
{
	int		built;

	if (ft_strequ(all->cmd.args[0], "cd"))
		change_directory(all);
	else if (ft_strequ(all->cmd.args[0], "env"))
		display_env(all);
	else if (ft_strequ(all->cmd.args[0], "setenv"))
		set_env(all, all->cmd.args[1], all->cmd.args[2]);
	else if (ft_strequ(all->cmd.args[0], "unsetenv"))
		unset_env(all, all->cmd.args[1]);
	else if (ft_strequ(all->cmd.args[0], "echo"))
		built_echo(&all->cmd);
	else if (ft_strequ(all->cmd.args[0], "exit"))
		exit_normal(all, ft_atoi(all->cmd.args[1]));
	else
		return (0);
	return (1);
}
