/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_2dchar_add.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: y0ja <y0ja@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/10 05:02:46 by y0ja              #+#    #+#             */
/*   Updated: 2015/05/10 05:02:47 by y0ja             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_2dchar_add(char **tab, char *add)
{
	int		i;
	int		len;
	char	**tmp;

	i = 0;
	len = ft_2dcharlen(tab);
	tmp = (char **)malloc(sizeof(char *) * (len + 2));
	if (!tmp)
		return (NULL);
	while (tab[i])
	{
		tmp[i] = tab[i];
		i++;
	}
	tmp[i] = add;
	tmp[i + 1] = NULL;
	free(tab);
	return (tmp);
}
