/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_output.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkeli <rkeli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 14:42:13 by rkeli             #+#    #+#             */
/*   Updated: 2019/06/05 22:19:15 by rkeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void		o_str(t_fractol *fractol)
{
	mlx_string_put(fractol->mlx, fractol->win, 50, 230, fractol->str_color,
			"Press 'PAGE DOWN' to set previous fractal");
	mlx_string_put(fractol->mlx, fractol->win, 50, 250, fractol->str_color,
			"Press 'R' to reset fractal");
	if (fractol->flg == 2)
		mlx_string_put(fractol->mlx, fractol->win, 50, HEIGHT - 50,
		fractol->str_color, "Press 'SPACE' to turn on or to turn off mouse");
}

void			string_output(t_fractol *fractol)
{
	fractol->str_color = (fractol->flg == 3 ? 0x000000 : 0xFFFFFF);
	mlx_string_put(fractol->mlx, fractol->win, 50, 50, fractol->str_color,
			"Press 'ESC' to close programm");
	mlx_string_put(fractol->mlx, fractol->win, 50, 70, fractol->str_color,
			"Press num + '+' or '-' to zoom or dezoom");
	mlx_string_put(fractol->mlx, fractol->win, 50, 90, fractol->str_color,
			"Turn the wheel to zoom or dezoom");
	mlx_string_put(fractol->mlx, fractol->win, 50, 110, fractol->str_color,
			"Press num + '*' or '/' to increase or reduce iterate");
	mlx_string_put(fractol->mlx, fractol->win, 50, 130, fractol->str_color,
			"Press 'UP' to move fractal up");
	mlx_string_put(fractol->mlx, fractol->win, 50, 150, fractol->str_color,
			"Press 'DOWN' to move fractal down");
	mlx_string_put(fractol->mlx, fractol->win, 50, 170, fractol->str_color,
			"Press 'RIGHT' to move fractal right");
	mlx_string_put(fractol->mlx, fractol->win, 50, 190, fractol->str_color,
			"Press 'LEFT' to move fractal left");
	mlx_string_put(fractol->mlx, fractol->win, 50, 210, fractol->str_color,
			"Press 'PAGE UP' to set next fractal");
	o_str(fractol);
}
