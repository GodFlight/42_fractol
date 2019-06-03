/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burningship.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkeli <rkeli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 14:04:10 by rkeli             #+#    #+#             */
/*   Updated: 2019/06/03 22:11:20 by rkeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void		burningship_calc(t_fractol *fractol)
{
	double tmp;
	double z_r;
	double z_i;

//	fractol->calc.c_r = 1.5 * (fractol->calc.x - WIDTH)
//						/ (0.5 * fractol->event.zoom * WIDTH) + 6;
//	fractol->calc.c_i = (fractol->calc.y - HEIGHT / 2)
//						/ (0.5 * fractol->event.zoom * HEIGHT) - 0.5;
//						fractol->calc.it = 0;
//	fractol->calc.c_r = 1.5 * (fractol->calc.x - WIDTH) / (0.5 * fractol->event.zoom * WIDTH) + WIDTH / 2;
	fractol->calc.c_r = fractol->calc.x * fractol->event.zoom + fractol->event.mve_horiz/* + ((WIDTH / 2) * fractol->event.zoom) + fractol->event.horiz*/;
	fractol->calc.c_i = fractol->calc.y * fractol->event.zoom + fractol->event.mve_vertic/* + ((HEIGHT / 2) * fractol->event.zoom) + fractol->event.vertic*/;
	fractol->calc.it = -100 + fractol->event.plus_it;
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

void	burningship(t_fractol *fractol)
{
	fractol->calc.y = 1;
	while (fractol->calc.y < HEIGHT - 1)
	{
		fractol->calc.x = 1;
		while (fractol->calc.x < WIDTH - 1)
		{
			burningship_calc(fractol);
			fractol->calc.x++;
		}
		fractol->calc.y++;
	}
	mlx_put_image_to_window(fractol->mlx, fractol->win, fractol->img.img, 0, 0);
}
