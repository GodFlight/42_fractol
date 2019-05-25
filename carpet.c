/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   carpet.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkeli <rkeli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 14:09:15 by rkeli             #+#    #+#             */
/*   Updated: 2019/05/25 14:09:15 by rkeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		carpet_calc(t_fractol *fractol)
{
	int		i;

	i = 0;
	fractol->calc.it = 0;
	int x = fractol->calc.x * fractol->event.zoom;
	int y = fractol->calc.y * fractol->event.zoom;
	x = ABS(x);
	y = ABS(y);
	while ((x > 0 || y > 0) && i < fractol->calc.it < fractol->event.it_max)
	{
		if (x % 3 == 1 && y % 3 == 1)
			break;
		x /= 3;
		y /= 3;
		fractol->calc.it++;
	}
	put_pixel_img(fractol->calc.x,
		  fractol->calc.y, fractol, ft_rgb_to_hex(255 - 9 * fractol->calc.it,
				  255 -  7 * fractol->calc.it,  255 -  12 * fractol->calc.it)/*ft_rgb_to_hex(255 - fractol->calc.it * 20, fractol->calc.it * 15, 0 )*/);
}