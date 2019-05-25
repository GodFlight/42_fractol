/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkeli <rkeli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 17:32:11 by rkeli             #+#    #+#             */
/*   Updated: 2019/05/04 03:46:20 by rkeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void *rs;

	if (size == (size_t)(-1))
		return (0);
	if (!(rs = malloc(size)))
		return (NULL);
	else
	{
		ft_bzero(rs, size);
		return (rs);
	}
}
