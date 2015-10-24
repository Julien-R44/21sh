/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <lubaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/25 02:22:43 by jripoute          #+#    #+#             */
/*   Updated: 2015/05/12 15:30:27 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

const char		*g_signals[] = {
	"",
	"Hangup",
	"",
	"Quit",
	"Illegal instruction",
	"Trace/BPT trap",
	"Abort trap",
	"EMT trap",
	"Floating point exception",
	"Killed",
	"Bus error",
	"Segmentation fault",
	"Bad system call",
	"",
	"Alarm clock",
	"Terminated",
	"",
	"Stopped",
	"Stopped",
	"",
	"",
	"Stopped",
	"Stopped",
	"",
	"Cputime limit exceeded",
	"Filesize limit exceeded",
	"Virtual timer expired",
	"Profiling timer expired",
	"",
	"",
	"User defined signal 1",
	"User defined signal 2",
	NULL
};

static void		handle_statut(int statut)
{
	int ret;

	if (!WIFSIGNALED(statut))
		return ;
	ret = WTERMSIG(statut);
	if (ret >= 0 && ret < 32 && g_signals[ret][0] != '\0')
	{
		ft_putstr_fd("\nft_sh1 : ", 2);
		ft_putstr_fd(g_signals[ret], 2);
		ft_putstr_fd(": ", 2);
		ft_putnbr_fd(ret, 2);
		ft_putchar_fd('\n', 2);
	}
}

pid_t	secure_fork(t_all *all)
{
	pid_t child;

	if ((child = fork()) == -1)
		ft_error(all, SYSCALL_FAIL);
	return (child);
}

void			exec_piped_process(t_all *all)
{
	pid_t	child;
	int		statut;
	int		pdes[2];

	pipe(pdes);
	child = secure_fork(all);
	if (child == 0)
	{
		dup2(pdes[WRITE_END], STDOUT_FILENO);
		close(pdes[READ_END]);
		if (execve(all->cmd.path, all->cmd.args, all->env.env) == -1)
			error_no_quit(NO_CMD_FOUND, all);
	}
	else
	{
		close(pdes[WRITE_END]);
		dup2(pdes[READ_END], STDIN_FILENO);
		wait(NULL);
	}
}

static int		set_flag_and_open_file_redir(char *file_redir, int redirtype)
{
	int		oflag;
	int		fd;

	if (file_redir == NULL)
		return (-1);
	oflag = O_RDWR | O_CREAT;
	if (redirtype == 2)
		oflag |= O_APPEND;
	else
		oflag |= O_TRUNC;
	fd = open(file_redir, oflag, 0644);
	return (fd);
}

void			exec_new_process(t_all *all, char *file_redir, int redirtype)
{
 	pid_t	child;
	int		statut;
	int		fd;

	if (all->cmd.path == NULL)
		return ;
	fd = set_flag_and_open_file_redir(file_redir, redirtype);
	child = secure_fork(all);
	if (child == 0)
	{
		if (file_redir)
		{
			dup2(fd, 1);
			close(fd);
		}
		if (execve(all->cmd.path, all->cmd.args, all->env.env) == -1)
			error_no_quit(NO_CMD_FOUND, all);
	}
	else
		waitpid(child, &statut, 0);
}
