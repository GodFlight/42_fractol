/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burningship.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkeli <rkeli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 14:04:10 by rkeli             #+#    #+#             */
/*   Updated: 2019/05/25 14:05:14 by rkeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		burningship_calc(t_fractol *fractol)
{
	double tmp;
	double z_r;
	double z_i;

	fractol->calc.c_r = 1.5 * (fractol->calc.x - WIDTH)
						/ (0.5 * fractol->event.zoom * WIDTH) + 3;
	fractol->calc.c_i = (fractol->calc.y - HEIGHT / 2)
						/ (0.5 * fractol->event.zoom * HEIGHT) - 0.5;
	fractol->calc.it = 0;
	z_r = 0;
	z_i = 0;
	while (z_i * z_i + z_r * z_r <= 4
			&& fractol->calc.it < fractol->event.it_max)
	{
		tmp = z_r;
		z_r = fabs(tmp * tmp) - z_i * z_i + fractol->calc.c_r;
		z_i = 2 * fabs(tmp * z_i) + fractol->calc.c_i;
		fractol->calc.it++;
	}
	if (fractol->calc.it >= fractol->event.it_max)
		put_pixel_img(fractol->calc.x, fractol->calc.y, fractol, 0x000000);
	else
		put_pixel_img(fractol->calc.x, fractol->calc.y, fractol,
					  ft_rgb_to_hex(255 - 9 * fractol->calc.it,  255 -  7
							* fractol->calc.it,  255 - 12 * fractol->calc.it));
}