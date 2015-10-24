/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_kebab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: y0ja <y0ja@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/10 04:30:22 by y0ja              #+#    #+#             */
/*   Updated: 2015/05/10 04:30:30 by y0ja             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_kebab(char *str, char *str2, ...)
{
	va_list	ap;
	char	*kebab;
	char	*arg;
	char	*tmp;

	va_start(ap, str2);
	kebab = ft_strjoin(str, str2);
	while ((arg = va_arg(ap, char *)) != NULL)
	{
		tmp = ft_strjoin(kebab, arg);
		free(kebab);
		kebab = tmp;
	}
	va_end(ap);
	return (kebab);
}
