/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: y0ja <y0ja@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/25 02:22:43 by jripoute          #+#    #+#             */
/*   Updated: 2015/05/11 03:37:32 by y0ja             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

#define ASSERT_F(x, y, e) if (x == y) {error_no_quit(e, all); return;}

static void	modify_env(t_all *all, char **env2del, char *newenv)
{
	if (*env2del)
		free(*env2del);
	*env2del = newenv;
	if (ft_strncmp(newenv, "PATH=", 5) == 0)
		reload_path_dirs(all);
}

void	set_env(t_all *all, char *var, char *value)
{
	char	*newenv;
	char	**env2del;

	env2del = NULL;
	ASSERT_F(var, NULL, NO_ENV2SET);
	newenv = ft_kebab(var, "=", value, NULL);
	if ((env2del = get_env_addr(all->env.env, newenv)) != NULL)
		modify_env(all, env2del, newenv);
	else
	{
		if ((all->env.env = ft_2dchar_add(all->env.env, newenv)) == NULL)
			ft_error(all, SYSCALL_FAIL);
	}
}

void	unset_env(t_all *all, char *var)
{
	char	**env2del;
	int		i;

	i = 1;
	env2del = NULL;
	ASSERT_F(var, NULL, NO_ENV2UNSET);
	if ((env2del = get_env_addr(all->env.env, var)) != NULL)
	{
		free(*env2del);
		while (env2del[i])
		{
			env2del[i - 1] = env2del[i];
			i++;
		}
		env2del[i - 1] = 0;
		if (ft_strequ(var, "PATH"))
			ft_2dchardel(&all->env.path_dir);
	}
	else
		error_no_quit(NO_ENV2UNSET, all);
}
