/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: y0ja <y0ja@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/30 03:18:56 by jripoute          #+#    #+#             */
/*   Updated: 2015/05/11 03:42:55 by y0ja             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static void		prepare_split_quot(unsigned int i, char *cmd)
{
	static int inquote = 0;

	if (i == 0)
		inquote = 0;
	if (*cmd == '"')
		inquote = (inquote++ == 2) ? 0 : inquote;
	if (*cmd == ' ' && inquote == 0)
		*cmd = '"';
}

char			**split_quotes(char **cmd)
{
	char	**array;
	char	*trimmed_cmd;

	trimmed_cmd = ft_strtrim(*cmd);
	ft_striteri(trimmed_cmd, prepare_split_quot);
	array = ft_strsplit(trimmed_cmd, '"');
	*cmd = trimmed_cmd;
	return (array);
}

char			**split_to_use(char *cmd)
{
	if (ft_charcount(cmd, '"') >= 2)
		return (split_quotes(&cmd));
	else
		return (ft_strsplit(cmd, ' '));
}
