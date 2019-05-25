/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkeli <rkeli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 17:18:46 by rkeli             #+#    #+#             */
/*   Updated: 2019/05/24 12:37:43 by rkeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

void	re_render(t_fractol *fractol)
{
	ft_bzero(fractol->img.data, fractol->img.line_size * HEIGHT);
	mlx_clear_window(fractol->mlx, fractol->win);
	mandelbrot(fractol);
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
		fractol->event.zoom += 0.005;
		re_render(fractol);
	}
	if (keycode == ZOOM_OUT)
	{
		fractol->event.zoom -= 0.005;
		re_render(fractol);
	}
	if (keycode == ITERATE_PLUS)
	{
		(fractol->event.it_max) + 10 == 150 ? 1 : (fractol->event.it_max += 10);
		(fractol->event.it_max) += 10;
		re_render(fractol);
	}
	if (keycode == ITERATE_MUNIS)
	{
		(fractol->event.it_max) - 10 == 0 ? 1 : (fractol->event.it_max -= 10);
		re_render(fractol);
	}
}

int 	mouse_move_event(int mousecode, int x, int y, t_fractol *fractol)
{/*
	if (mousecode == 4)
		(fractol->event.mouse_move) += 0.1;
	else if (mousecode == 5)
		(fractol->event.mouse_move) -= 0.1;
	re_render(fractol);*/
}