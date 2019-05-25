/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkeli <rkeli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 14:14:38 by rkeli             #+#    #+#             */
/*   Updated: 2019/05/25 14:18:11 by rkeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		julia(t_fractol *fractol)
{
	double	tmp;

	fractol->calc.c_i = 1.5 * (fractol->calc.x - WIDTH / 2)
						/ (fractol->event.zoom * 0.5 * WIDTH) + 0.9;
	fractol->calc.c_r = 1.0 * (fractol->calc.y - HEIGHT / 2)
						/ (fractol->event.zoom * 0.5 * HEIGHT) + 0.9;
	fractol->calc.it = 0;
	while (fractol->calc.c_i * fractol->calc.c_i + fractol->calc.c_r
		* fractol->calc.c_r <= 4 && fractol->calc.it < fractol->event.it_max)
	{
		tmp = fractol->calc.c_i;
		fractol->calc.c_i = fractol->calc.c_i * fractol->calc.c_i
							- fractol->calc.c_r
							* fractol->calc.c_r + fractol->event.mouse_move;
		fractol->calc.c_r = 2.0 * tmp * fractol->calc.c_r
							+ fractol->event.mouse_move;
		fractol->calc.it++;
	}
	if (fractol->calc.it == fractol->event.it_max)
		put_pixel_img(fractol->calc.x, fractol->calc.y, fractol, 0x000000);
	else
		put_pixel_img(fractol->calc.x, fractol->calc.y, fractol,
				ft_rgb_to_hex(255 - 9 * fractol->calc.it, 255 - 7
				* fractol->calc.it, 255 - 12 * fractol->calc.it));
}
