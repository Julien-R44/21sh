/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: y0ja <y0ja@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/26 06:35:22 by jripoute          #+#    #+#             */
/*   Updated: 2015/05/10 00:46:41 by y0ja             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static void		display_hour(void)
{
	time_t		epoch_time;
	char		*str;
	int			i;

	i = 11;
	epoch_time = time(NULL);
	str = asctime(localtime(&epoch_time));
	ft_putstr(FG_LGREY);
	while (i < 16)
	{
		ft_putchar(str[i]);
		i++;
	}
}

static void		display_pwd(t_all *all)
{
	char	*val;
	char	*home;
	int		len;

	val = get_env(all->env.env, "PWD=");
	home = get_env(all->env.env, "HOME=");
	len = ft_strlen(home);
	if (val && home && ft_strncmp(val, home, len) == 0)
	{
		ft_putchar('~');
		ft_putstr(&val[len]);
	}
	else
		ft_putstr(val);
}

void			display_prompt(t_all *all)
{
	ft_putstr("$ ");
	ft_putstr(FG_MAGENTA);
	ft_putstr(get_env(all->env.env, "USER="));
	ft_putstr(FG_RESET);
	ft_putstr(" ~ ");
	ft_putstr(FG_BROWN);
	display_pwd(all);
	ft_putstr(FG_RESET);
	ft_putstr(" - ");
	display_hour();
	ft_putstr(FG_RESET);
	ft_putstr(" > ");
}
