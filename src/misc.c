/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: y0ja <y0ja@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/25 02:22:43 by jripoute          #+#    #+#             */
/*   Updated: 2015/05/11 03:42:03 by y0ja             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

char	*get_env(char **env, char *var)
{
	int i;
	int	len;

	i = 0;
	len = ft_strlen(var);
	while (env[i] && ft_strncmp(env[i], var, len) != 0)
		i++;
	if (env[i])
		return (&env[i][len]);
	return (NULL);
}

char	**get_env_addr(char **env, char *var)
{
	int i;
	int	len;

	i = 0;
	len = ft_strclen(var, '=');
	while (env[i] && ft_strncmp(env[i], var, len) != 0)
		i++;
	if (env[i])
		return (&env[i]);
	return (NULL);
}

void	reload_path_dirs(t_all *all)
{
	ft_2dchardel(&all->env.path_dir);
	all->env.path_dir = get_path_dirs(all->env.env);
}

void	del_tabulation(char *c)
{
	if (*c == '\t')
		*c = ' ';
}

int		is_not_escaped(char c, char c2, char c_prev)
{
	if (c == c2 && c_prev != '\\')
		return (1);
	return (0);
}

t_all	*f_all(t_all *all)
{
	static t_all	*ret = NULL;

	if (ret == NULL)
		ret = all;
	return (ret);
}

int		fputchar(int c)
{
	ft_putchar_fd(c, 2);
	return (1);
}

void	tgetstr_cpb(char *cpb)
{
	char *res;

	if ((res = tgetstr(cpb, NULL)) == NULL)
		ft_error(f_all(NULL), GETATTR);
	tputs(res, 0, fputchar);
}

