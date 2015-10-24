/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <lubaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/25 02:22:43 by jripoute          #+#    #+#             */
/*   Updated: 2015/05/12 15:36:21 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

extern char **environ;

char	*redirected_in_args(char **args, int *redir_type)
{
	int		i;
	char	*file_redir;

	i = 0;
	while (args[i])
	{
		if (ft_strequ(args[i], ">") || ft_strequ(args[i], ">>"))
		{
			if (ft_strequ(args[i], ">"))
				*redir_type = 1;
			else
				*redir_type = 2;
			free(args[i]);
			file_redir = args[i + 1];
			args[i] = NULL;
			args[i + 1] = NULL;
			return (file_redir);
		}
		i++;
	}
	return (NULL);
}

void	exec_cmd_input(t_all *all)
{
	int		i;
	int		last_cmd;
	char	*file_redir;
	int		redir_type;

	i = 0;
	last_cmd = 0;
	while (all->cmd.to_pipe[i])
	{
		if (!all->cmd.to_pipe[i+1])
			last_cmd = 1;
		all->cmd.args = split_to_use(all->cmd.to_pipe[i]);
		if (cmd_is_builtin(all) == 0)
		{
			search_binary_in_path_dirs(all, all->cmd.args[0]);
			file_redir = redirected_in_args(all->cmd.args, &redir_type);
			if (ft_2dcharlen(&all->cmd.to_pipe[i]) > 1)
				exec_piped_process(all);
			else
				exec_new_process(all, file_redir, redir_type);
		}
		ft_2dchardel(&all->cmd.args);
		i++;
	}
}

int		main(void)
{
	t_all	all;
	int		i;

	f_all(&all);
	init_shell(&all, environ);
	while (42)
	{
		i = 0;
		display_prompt(&all);
		all.env.cmd2exec = scan_for_input(&all);
		while (all.env.cmd2exec[i])
		{
			if (parse_cmd(&all, all.env.cmd2exec[i]))
				exec_cmd_input(&all);
			free_cmd(&all.cmd);
			i++;
		}
		free(all.env.cmd2exec[i]);
		ft_memdel((void **)&all.env.cmd2exec);
	}
	return (0);
}
