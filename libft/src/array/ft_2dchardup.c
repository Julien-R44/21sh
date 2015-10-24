/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_2dchardup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: y0ja <y0ja@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/10 03:41:51 by y0ja              #+#    #+#             */
/*   Updated: 2015/05/10 19:31:27 by y0ja             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_2dchardup(char **tab)
{
	size_t	len;
	size_t	i;
	char	**newtab;

	i = 0;
	len = ft_2dcharlen(tab);
	newtab = (char **)malloc(sizeof(char *) * (len + 1));
	while (i < len)
	{
		newtab[i] = strdup(tab[i]);
		i++;
	}
	newtab[i] = NULL;
	return (newtab);
}
