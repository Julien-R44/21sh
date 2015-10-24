/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: y0ja <y0ja@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/25 02:22:43 by jripoute          #+#    #+#             */
/*   Updated: 2015/05/11 04:34:08 by y0ja             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void	reset_term(t_all *all)
{
	if (tcsetattr(all->term.tty, 0, &all->term.oldterm) == -1)
		ft_error(all, GETATTR);
}

void	free_cmd(t_cmd *cmd)
{
	// ft_2dchardel(&cmd->args);
	ft_2dchardel(&cmd->to_pipe);
	if (cmd->path)
		ft_memdel((void **)&cmd->path);
}

void	free_all(t_all *all)
{
	if (all->env.env)
		ft_2dchardel(&all->env.env);
	if (all->env.path_dir)
		ft_2dchardel(&all->env.path_dir);
	if (all->cmd.args)
		free_cmd(&all->cmd);
	if (all->env.cmd2exec)
		ft_2dchardel(&all->env.cmd2exec);
}

void	exit_normal(t_all *all, int exit_ret)
{
	if (exit_ret != 42)
		free_all(all);
	reset_term(all);
	exit(exit_ret);
}

void	error_no_quit(int er, t_all *all)
{
	if (er == NO_CMD_FOUND)
	{
		ft_putstr(all->cmd.args[0]);
		ft_putstr(" : commande introuvable\n");
	}
	if (er == NO_ENV2UNSET)
	{
		ft_putstr(all->cmd.args[1]);
		ft_putstr(" : no var. with this name to unset\n");
	}
	if (er == NO_ENV2SET)
		ft_putstr("setenv : bad utilisation : setenv VAR [VALUE]\n");
	if (er == NO_SUCH_FILE)
	{
		ft_putstr(all->cmd.args[0]);
		ft_putstr(" : no such file or directory : \n");
		ft_putstr(all->cmd.args[1]);
	}
	if (er == PERM_DENIED)
	{
		ft_putstr(all->cmd.args[0]);
		ft_putstr(" : Permission Denied\n");
	}
}

int		get_error(t_all *all, int er, void *data)
{
	int ret;

	if (er == OPENDIR_FAIL)
	{
		ret = access((char *)data, F_OK);
		if (ret == 0)
			ft_error(all, SYSCALL_FAIL);
		return (0);
	}
	return (0);
}

void	ft_error(t_all *all, int er)
{
	if (er == SYSCALL_FAIL)
		ft_putstr("A syscall failed...\n");
	if (er == NOTERMENV)
		printf("Specify terminal with setenv TERM.\n");
	else if (er == TERMINFODB)
		printf("Terminfo database could not be found.\n");
	else if (er == TERMNOTDEF)
		printf("Specified term is not defined.\n");
	else if (er == GETATTR)
		printf("tcgetattr() | tcsetattr() | tgetX() failed.\n");
	free_all(all);
	reset_term(all);
	exit(-1);
}
