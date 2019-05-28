/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkeli <rkeli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 17:18:46 by rkeli             #+#    #+#             */
/*   Updated: 2019/05/29 00:05:57 by rkeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

void	render(t_fractol *fractol)
{

	ft_bzero(fractol->img.data, fractol->img.line_size * HEIGHT);
	mlx_clear_window(fractol->mlx, fractol->win);
	if (fractol->flg == 1)
		mandelbrot(fractol);
	else if (fractol->flg == 2)
		julia(fractol);
	else if (fractol->flg == 3)
		carpet(fractol);
	else
		burningship(fractol);
}

int		ft_close(void *param)
{
	(void)param;
	exit(0);
	return (0);
}

int 	key_event(int keycode, void *param)
{
	t_fractol *fractol;

	fractol = (t_fractol *)param;
	if (keycode == ESC)
		exit (0);
	if (keycode == ZOOM_INTO)
	{
		fractol->event.zoom > 0 ? fractol->event.zoom -= 0.0005 : 1;
		fractol->event.plus_it -= 1;
	}
	if (keycode == ZOOM_OUT)
	{
		fractol->event.zoom += 0.0005;
		fractol->event.plus_it += 1;
	}
	if (keycode == ITERATE_PLUS)
		(fractol->event.it_max) + 10 == 150 ? 1 : (fractol->event.it_max += 10);
	if (keycode == ITERATE_MUNIS)
		(fractol->event.it_max) - 10 == 0 ? 1 : (fractol->event.it_max -= 10);
	if (keycode == UP)
	{
		fractol->event.vertic += 0.05;
		printf("vertic: %.20Lf\n", fractol->event.mve_vertic);
	}
	if (keycode == DOWN)
	{
		fractol->event.vertic -= 0.05;
		printf("vertic: %.20Lf\n", fractol->event.mve_vertic);
	}
	if (keycode == RIGHT)
	{
		fractol->event.horiz -= 0.05;
		printf("horiz: %.20Lf\n", fractol->event.mve_horiz);
	}
	if (keycode == LEFT)
	{
		fractol->event.horiz += 0.05;
		printf("horiz: %.20Lf\n", fractol->event.mve_vertic);
	}
	if (keycode == JUMP)
		fractol->jflg + 1 < 3 ? fractol->jflg += 1 : 1;
	run_cl(fractol);
}

void 	mouse_move_event( int x, int y, void *param)
{
	t_fractol	*fractol;
	fractol = (t_fractol *)param;

	if (fractol->flg == 2)
	{
		fractol->event.mouse_move_x += (long double)x / 100000;
		fractol->event.mouse_move_y += (long double)y / 100000;
		printf("y: %Lf\n", fractol->event.mouse_move_y);
		printf("x: %Lf\n", fractol->event.mouse_move_x);
	}
	run_cl(fractol);
//	if (mousecode == 4)
//		(fractol->event.mouse_move) += 0.1;
//	else if (mousecode == 5)
//		(fractol->event.mouse_move) -= 0.1;
//	re_render(fractol);

}

//void 	jump_mandelbrot(int keycode, void * param)
//{
//	t_fractol *fractol;
//
//	fractol = (t_fractol *)param;
//	if (keycode == JUMP)
//		fractol->flg + 1 > 3 ? fractol->flg += 1 : fractol->flg == 0;
//}
