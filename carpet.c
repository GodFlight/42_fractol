/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   carpet.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkeli <rkeli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 14:09:15 by rkeli             #+#    #+#             */
/*   Updated: 2019/05/25 14:09:52 by rkeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void		carpet_calc(t_fractol *fractol)
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
				  255 -  7 * fractol->calc.it,  255 -  12 * fractol->calc.it));
}

void	carpet(t_fractol *fractol)
{
	fractol->calc.y = 1;
	while (fractol->calc.y < HEIGHT - 1)
	{
		fractol->calc.x = 1;
		while (fractol->calc.x < WIDTH - 1)
		{
			carpet_calc(fractol);
			fractol->calc.x++;
		}
		fractol->calc.y++;
	}
	mlx_put_image_to_window(fractol->mlx, fractol->win, fractol->img.img, 0, 0);
}
