/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkeli <rkeli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 18:47:01 by rkeli             #+#    #+#             */
/*   Updated: 2019/06/06 22:31:40 by rkeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_updt(char *str, char *update)
{
	char *nw;

	nw = update;
	if (str != NULL)
		free(str);
	str = update;
	return (str);
}
