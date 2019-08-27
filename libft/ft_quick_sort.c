/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quick_sort.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 18:55:53 by sbecker           #+#    #+#             */
/*   Updated: 2019/08/21 23:25:56 by rkeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	q_sort(float *arr, int *index_arr, int left, int right)
{
	int		l_hold;
	int		r_hold;
	float	pivot;

	pivot = arr[(left + right) / 2];
	l_hold = left;
	r_hold = right;
	while (left <= right)
	{
		while (arr[left] > pivot)
			left++;
		while (arr[right] < pivot)
			right--;
		if (left <= right)
		{
			ft_fswap(&arr[left], &arr[right]);
			ft_swap(&index_arr[left], &index_arr[right]);
			left++;
			right--;
		}
	}
	if (l_hold < right)
		q_sort(arr, index_arr, l_hold, right);
	if (r_hold > left)
		q_sort(arr, index_arr, left, r_hold);
}

int		*quick_sort(float *arr, int size)
{
	int		*index_arr;
	int		i;

	index_arr = (int *)malloc(sizeof(int) * size);
	i = -1;
	while (++i < size)
		index_arr[i] = i;
	q_sort(arr, index_arr, 0, size - 1);
	return (index_arr);
}
