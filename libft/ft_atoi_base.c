/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkeli <rkeli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 18:59:30 by rkeli             #+#    #+#             */
/*   Updated: 2019/05/09 21:16:58 by rkeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

/*
static char		*skip_something(char *str)
{
	while (*str == ' ' || *str == '\r' || *str == '\v' || *str == '\t'
		   || *str == '\n' || *str == '\f')
		str++;
	return (str);
}

int		ft_atoi_base(const char *str, int base)
{
	char 			*max_base;
	unsigned long	res;
	int 			sgn;

	res = 0;
	sgn = 1;
	max_base = "0123456789ABCDEF\0";

	if (base == 10)
		return (ft_atoi(str));
	str = skip_something(str);
	if (*str == '+')
		str++;
	else if (*str == '-' && base == 10)
	{
		str++;
		sgn = -1;
	}
	while (!(ft_strchr(*str, base)))
	{

		str++;
	}

}
*/
