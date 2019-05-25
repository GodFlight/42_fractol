/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkeli <rkeli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 18:35:30 by rkeli             #+#    #+#             */
/*   Updated: 2019/05/04 03:46:20 by rkeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*srch;

	srch = (unsigned char*)s;
	while (n--)
	{
		if (*srch == (unsigned char)c)
			return ((void*)srch);
		srch++;
	}
	return (0);
}
