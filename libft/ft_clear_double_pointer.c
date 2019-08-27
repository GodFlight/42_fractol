/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clear_double_pointer.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 04:09:21 by sbecker           #+#    #+#             */
/*   Updated: 2019/08/19 04:09:27 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_clear_double_pointer(void **arr, int size)
{
	int	i;

	if (arr && *arr)
	{
		i = 0;
		while (i < size)
		{
			free(arr[i]);
			arr[i] = NULL;
			i++;
		}
		free(arr);
	}
}
