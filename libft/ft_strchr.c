/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkeli <rkeli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 16:54:50 by rkeli             #+#    #+#             */
/*   Updated: 2019/05/04 03:46:20 by rkeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*cpy;

	cpy = (char*)s;
	i = 0;
	while (cpy[i] != '\0')
	{
		if (cpy[i] == c)
			return (&cpy[i]);
		i++;
	}
	if (cpy[i] == c)
		return (&cpy[i]);
	return (NULL);
}
