/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_bin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: y0ja <y0ja@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/25 02:22:43 by jripoute          #+#    #+#             */
/*   Updated: 2015/05/10 21:22:57 by y0ja             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

int		bin_is_here(t_all *all, char *bin, char *path_dir)
{
	DIR				*dir;
	t_dirent		*dirent;
	char			*newstr;
	int				ret;

	if ((dir = opendir(path_dir)) == NULL)
		return (get_error(all, OPENDIR_FAIL, path_dir));
	while ((dirent = readdir(dir)) != NULL)
	{
		if (ft_strequ(dirent->d_name, bin))
		{
			newstr = ft_strjoin(path_dir, bin);
			ret = access(newstr, X_OK);
			free(newstr);
			if (ret == 0)
				return (1);
			return (-1);
		}
	}
	closedir(dir);
	return (0);
}

void	search_binary_in_path_dirs(t_all *all, char *bin)
{
	int i;
	int ret;

	i = 0;
	if (ft_strchr(bin, '/') != NULL)
	{
		all->cmd.path = ft_strdup(bin);
		return ;
	}
	while (all->env.path_dir && all->env.path_dir[i])
	{
		ret = bin_is_here(all, bin, all->env.path_dir[i]);
		if (ret == 1 || ret == -1)
		{
			if (ret == 1)
				all->cmd.path = ft_kebab(all->env.path_dir[i], "/", bin, NULL);
			if (ret == -1)
				error_no_quit(PERM_DENIED, all);
			break ;
		}
		i++;
	}
	if (!all->env.path_dir || !all->env.path_dir[i])
		error_no_quit(NO_CMD_FOUND, all);
}
