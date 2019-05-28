/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkeli <rkeli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 14:14:38 by rkeli             #+#    #+#             */
/*   Updated: 2019/05/28 18:08:54 by rkeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void		julia_calc(t_fractol *fractol)
{
	double	tmp;

//	fractol->calc.c_i = 1.5 * (fractol->calc.x - WIDTH / 2)
//			/ (fractol->event.zoom * 0.5 * WIDTH) + 0.9;
//	fractol->calc.c_r = 1.0 * (fractol->calc.y - HEIGHT / 2)
//			/ (fractol->event.zoom * 0.5 * HEIGHT) + 0.9;
	fractol->calc.c_r = fractol->calc.x * fractol->event.zoom + -((WIDTH / 2) * fractol->event.zoom) + fractol->event.horiz;
	fractol->calc.c_i = fractol->calc.y * fractol->event.zoom + -((HEIGHT / 2) * fractol->event.zoom) + fractol->event.vertic;
	fractol->calc.it = -100 + fractol->event.plus_it;
	while (fractol->calc.c_i * fractol->calc.c_i + fractol->calc.c_r
	* fractol->calc.c_r <= 4 && fractol->calc.it < fractol->event.it_max)
	{
		tmp = fractol->calc.c_i;
		fractol->calc.c_i = fractol->calc.c_i * fractol->calc.c_i
				- fractol->calc.c_r
				* fractol->calc.c_r + fractol->event.mouse_move_x;
		fractol->calc.c_r = 2.0 * tmp * fractol->calc.c_r
				+ fractol->event.mouse_move_y;
		fractol->calc.it++;
	}
	if (fractol->calc.it == fractol->event.it_max)
		put_pixel_img(fractol->calc.x, fractol->calc.y, fractol, 0x000000);
	else
		put_pixel_img(fractol->calc.x, fractol->calc.y, fractol,
					  ft_rgb_to_hex(255 - 9 * fractol->calc.it,  255 -  7
					  * fractol->calc.it,  255 -  12 * fractol->calc.it));
}

void	julia(t_fractol *fractol)
{
	fractol->calc.y = 1;
	while (fractol->calc.y < HEIGHT - 1)
	{
		fractol->calc.x = 1;
		while (fractol->calc.x < WIDTH - 1)
		{
			julia_calc(fractol);
			fractol->calc.x++;
		}
		fractol->calc.y++;
	}
	mlx_put_image_to_window(fractol->mlx, fractol->win, fractol->img.img, 0, 0);
}
