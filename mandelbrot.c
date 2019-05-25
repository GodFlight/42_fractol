/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkeli <rkeli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 18:07:43 by rkeli             #+#    #+#             */
/*   Updated: 2019/05/25 14:19:36 by rkeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		ft_rgb_to_hex(int r, int g, int b)
{
	int res = 0;
	res = r << 16 | g << 8 | b;
	return (res);
}

//void		burningship_calc(t_fractol *fractol)
//{
//	double tmp;
//	double z_r;
//	double z_i;
//
//	fractol->calc.c_r = 1.5 * (fractol->calc.x - WIDTH)
//			/ (0.5 * fractol->event.zoom * WIDTH) + 3;
//	fractol->calc.c_i = (fractol->calc.y - HEIGHT / 2)
//			/ (0.5 * fractol->event.zoom * HEIGHT) - 0.5;
//	fractol->calc.it = 0;
//	z_r = 0;
//	z_i = 0;
//	while (z_i * z_i + z_r * z_r <= 4 && fractol->calc.it < fractol->event.it_max)
//	{
//		tmp = z_r;
//		z_r = fabs(tmp * tmp) - z_i * z_i + fractol->calc.c_r;
//		z_i = 2 * fabs(tmp * z_i) + fractol->calc.c_i;
//		fractol->calc.it++;
//	}
//	if (fractol->calc.it >= fractol->event.it_max)
//		put_pixel_img(fractol->calc.x, fractol->calc.y, fractol, 0x000000);
//	else
//		put_pixel_img(fractol->calc.x, fractol->calc.y, fractol,
//					  ft_rgb_to_hex(255 - 9 * fractol->calc.it,  255 -  7
//					  * fractol->calc.it,  255 - 12 * fractol->calc.it));
//}

//void		carpet_calc(t_fractol *fractol)
//{
//	int		i;
//
//	i = 0;
//	fractol->calc.it = 0;
//	int x = fractol->calc.x * fractol->event.zoom;
//	int y = fractol->calc.y * fractol->event.zoom;
//	x = ABS(x);
//	y = ABS(y);
//	while ((x > 0 || y > 0) && i < fractol->calc.it < fractol->event.it_max)
//	{
//		if (x % 3 == 1 && y % 3 == 1)
//			break;
//		x /= 3;
//		y /= 3;
//		fractol->calc.it++;
//	}
//	put_pixel_img(fractol->calc.x,
//			fractol->calc.y, fractol, ft_rgb_to_hex(255 - 9 * fractol->calc.it,
//					255 -  7 * fractol->calc.it,  255 -  12 * fractol->calc.it)/*ft_rgb_to_hex(255 - fractol->calc.it * 20, fractol->calc.it * 15, 0 )*/);
//}

//void		julia(t_fractol *fractol)
//{
//	double	tmp;
//
//	fractol->calc.c_i = 1.5 * (fractol->calc.x - WIDTH / 2)
//			/ (fractol->event.zoom * 0.5 * WIDTH) + 0.9;
//	fractol->calc.c_r = 1.0 * (fractol->calc.y - HEIGHT / 2)
//			/ (fractol->event.zoom * 0.5 * HEIGHT) + 0.9;
//	fractol->calc.it = 0;
//	while (fractol->calc.c_i * fractol->calc.c_i + fractol->calc.c_r
//	* fractol->calc.c_r <= 4 && fractol->calc.it < fractol->event.it_max)
//	{
//		tmp = fractol->calc.c_i;
//		fractol->calc.c_i = fractol->calc.c_i * fractol->calc.c_i
//				- fractol->calc.c_r
//				* fractol->calc.c_r + fractol->event.mouse_move;
//		fractol->calc.c_r = 2.0 * tmp * fractol->calc.c_r
//				+ fractol->event.mouse_move;
//		fractol->calc.it++;
//	}
//	if (fractol->calc.it == fractol->event.it_max)
//		put_pixel_img(fractol->calc.x, fractol->calc.y, fractol, 0x000000);
//	else
//		put_pixel_img(fractol->calc.x, fractol->calc.y, fractol,
//					  ft_rgb_to_hex(255 - 9 * fractol->calc.it,  255 -  7
//					  * fractol->calc.it,  255 -  12 * fractol->calc.it));
//		/*put_pixel_img(fractol->calc.x, fractol->calc.y, fractol,
//				fractol->event.color * fractol->calc.it);*/
//}

void		mandelbrot_calc(t_fractol *fractol) // TODO Добавь ивент на радугу для фрактала (перемножение цвета на зум)
{
	double  tmp;

	fractol->calc.c_r = 1.5 * (fractol->calc.x * 1.5 - WIDTH / 1.5)
			/ (fractol->event.zoom * 1 * WIDTH); // TODO Добавь ивент на движение по мапе + отцентровка
	fractol->calc.c_i = (fractol->calc.y * 1.5 - HEIGHT / 1.5)
			/ (fractol->event.zoom * 1 * HEIGHT);
	fractol->calc.z_i = 0;
	fractol->calc.z_r = 0;
	fractol->calc.it = -500;
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
			//mandelbrot_calc(fractol);
			julia(fractol);
			//burningship_calc(fractol);
			fractol->calc.x++;
		}
		fractol->calc.y++;
	}
	mlx_put_image_to_window(fractol->mlx, fractol->win, fractol->img.img, 0, 0);
}
