/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkeli <rkeli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 18:07:43 by rkeli             #+#    #+#             */
/*   Updated: 2019/05/28 19:17:10 by rkeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

int		ft_rgb_to_hex(int r, int g, int b)
{
	int res = 0;
	res = r << 16 | g << 8 | b;
	return (res);
}

static void		jump(t_fractol *fractol)
{
	if (fractol->jflg == 0)
	{
		fractol->event.mve_horiz = -((WIDTH / 2) * fractol->event.zoom) + fractol->event.horiz;
		fractol->event.mve_vertic =  -((HEIGHT / 2) * fractol->event.zoom) + fractol->event.vertic;
		fractol->calc.it = -100;
	}
//	if (fractol->jflg == 0)
//	{
//		fractol->event.zoom = 0.00000000032;
//		fractol->event.mve_horiz = -0.777807810193171 - fractol->event.horiz;
//		fractol->event.mve_vertic = 0.131645108003206 - fractol->event.vertic;
//		fractol->calc.it = -750;
//	}
////	if (fractol->jflg == 0)
//	{
//		fractol->event.mve_horiz = -1.96680095;
//		fractol->event.mve_vertic = 0.00000478;
//		fractol->event.zoom = 0.00000014;
//	}
//	if (fractol->jflg == 0)
//	{
//		fractol->event.mve_horiz = -1.7433419053321;
//		fractol->event.mve_vertic = 0.0000907687489;
//		fractol->event.zoom = 0.00000000374;
//	}
}

static void		mandelbrot_calc(t_fractol *fractol) // TODO Добавь ивент на радугу для фрактала (перемножение цвета на зум)
{
	double  tmp;

//	fractol->calc.c_r = 1.5 * (fractol->calc.x * 1.5 - WIDTH / 1.5)
//			/ (fractol->event.zoom * 1 * WIDTH); // TODO Добавь ивент на движение по мапе + отцентровка
//	fractol->calc.c_i = (fractol->calc.y * 1.5 - HEIGHT / 1.5)
//			/ (fractol->event.zoom * 1 * HEIGHT);
	//jump(fractol);
	fractol->event.mve_horiz = -((WIDTH / 2) * fractol->event.zoom) + fractol->event.horiz;
	fractol->event.mve_vertic =  -((HEIGHT / 2) * fractol->event.zoom) + fractol->event.vertic;
	fractol->calc.c_r = (fractol->calc.x * fractol->event.zoom) + fractol->event.mve_horiz;
	fractol->calc.c_i = fractol->calc.y * fractol->event.zoom + fractol->event.mve_vertic;
	fractol->calc.z_i = 0;
	fractol->calc.z_r = 0;
	fractol->calc.it = -100 + fractol->event.plus_it;
	while (fractol->calc.z_i * fractol->calc.z_i + fractol->calc.z_r
			* fractol->calc.z_r <= 4 && fractol->calc.it < fractol->event.it_max)
	{
		tmp = fractol->calc.z_r;
		fractol->calc.z_r = tmp * tmp - fractol->calc.z_i * fractol->calc.z_i
				+ fractol->calc.c_r;
		fractol->calc.z_i = 2 * tmp * fractol->calc.z_i + fractol->calc.c_i;
		fractol->calc.it++;
	}
	/*if (fractol->calc.it == fractol->event.it_max)
		put_pixel_img(fractol->calc.x, fractol->calc.y, fractol, 0x000000);*/
	if (fractol->calc.it >= fractol->event.it_max)
		put_pixel_img(fractol->calc.x, fractol->calc.y, fractol, 0x000000);
	else
		put_pixel_img(fractol->calc.x, fractol->calc.y, fractol,
				ft_rgb_to_hex(255 - 9 * fractol->calc.it,  255 -  7
				* fractol->calc.it,  255 - 12 * fractol->calc.it));

}

void	mandelbrot(t_fractol *fractol)
{
	fractol->calc.y = 1;
	while (fractol->calc.y < HEIGHT - 1)
	{
		fractol->calc.x = 1;
		while (fractol->calc.x < WIDTH - 1)
		{
			mandelbrot_calc(fractol);
			fractol->calc.x++;
		}
		fractol->calc.y++;
	}
	printf("check\n");
	mlx_put_image_to_window(fractol->mlx, fractol->win, fractol->img.img, 0, 0);
}
