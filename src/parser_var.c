/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jripoute <jripoute@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/26 04:39:42 by jripoute          #+#    #+#             */
/*   Updated: 2015/01/30 03:18:18 by jripoute         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

char	*replace_var(t_all *all, char *cmd)
{
	int		i;
	int		index_end_var;
	char	*first;
	char	*newstr;

	i = 0;
	first = NULL;
	newstr = NULL;
	while (cmd[i])
	{
		if (cmd[i] == '$' && cmd[i - 1] != '\\')
		{
			i++;
			cmd[i - 1] = 0;
			first = ft_strjoin(cmd, matching_var(all, cmd, i, &index_end_var));
			newstr = ft_strjoin(first, &cmd[index_end_var]);
			free(cmd);
			free(first);
			cmd = newstr;
			i = 0;
		}
		i++;
	}
	return (cmd);
}

char	*matching_var(t_all *all, char *cmd, int i, int *index_end_var)
{
	int		j;
	char	tmp;
	char	tmp2;
	char	*value;

	j = i;
	while (cmd[j] && ft_isalnum(cmd[j]))
		j++;
	tmp = cmd[j];
	tmp2 = cmd[j + 1];
	cmd[j] = '=';
	cmd[j + 1] = 0;
	value = get_env(all->env.env, &cmd[i]);
	cmd[j] = tmp;
	cmd[j + 1] = tmp2;
	*index_end_var = j;
	return (value);
}
