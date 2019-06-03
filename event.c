/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkeli <rkeli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 17:18:46 by rkeli             #+#    #+#             */
/*   Updated: 2019/06/03 22:28:33 by rkeli            ###   ########.fr       */
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
	else if (keycode == ZOOM_INTO)
	{
		fractol->event.zoom -= (fractol->event.zoom * 0.05);
//		fractol->event.mve_horiz = -((WIDTH / 2) * fractol->event.zoom);
//		fractol->event.mve_vertic = -((HEIGHT / 2) * fractol->event.zoom);
		fractol->event.mve_horiz += fractol->event.mouse_move_x * fractol->event.zoom * 0.05;
		fractol->event.mve_vertic += fractol->event.mouse_move_y * fractol->event.zoom * 0.05;
		fractol->event.plus_it -= 1;
	}
	else if (keycode == ZOOM_OUT)
	{
		fractol->event.zoom += (fractol->event.zoom * 0.05);
//		fractol->event.mve_horiz = -((WIDTH / 2) * fractol->event.zoom);
//		fractol->event.mve_vertic = -((HEIGHT / 2) * fractol->event.zoom);
		fractol->event.mve_horiz -= fractol->event.mouse_move_x * fractol->event.zoom * 0.05;
		fractol->event.mve_vertic -= fractol->event.mouse_move_y * fractol->event.zoom * 0.05;
		fractol->event.plus_it += 1;
	}
	else if (keycode == ITERATE_PLUS)
		fractol->event.it_max += 10;
	else if (keycode == ITERATE_MUNIS)
		(fractol->event.it_max) - 10 == 0 ? 1 : (fractol->event.it_max -= 10);
	else if (keycode == UP)
		fractol->event.vertic += (fractol->event.zoom * 17);
	else if (keycode == DOWN)
		fractol->event.vertic -= (fractol->event.zoom * 17);
	else if (keycode == RIGHT)
		fractol->event.horiz -= (fractol->event.zoom * 17);
	else if (keycode == LEFT)
		fractol->event.horiz += (fractol->event.zoom * 17);
	else if (keycode == JUMP)
		fractol->jflg + 1 < 3 ? fractol->jflg += 1 : 1;
	else if (keycode == SPACE)
	{
//		fractol->event.stop_jl == 0 ? fractol->event.stop_jl = 1 : fractol->event.stop_jl = 0;
		if (fractol->event.stop_jl == 0)
			fractol->event.stop_jl = 1;
		else
			fractol->event.stop_jl = 0;
//		printf("STOP? [%d]\n", fractol->event.stop_jl);
	}
	ft_bzero(fractol->img.data, fractol->img.line_size * HEIGHT);
	mlx_clear_window(fractol->mlx, fractol->win);
//	render(fractol);
	run_cl(fractol);
}

void 	mouse_event(int mousecode, int x, int y, void *param)
{
	t_fractol	*fractol;
	fractol = (t_fractol *)param;

	if (x > WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	fractol->event.mouse_move_x = x;
	fractol->event.mouse_move_y = y;
	if (mousecode == 4 || mousecode == 1)
	{
		fractol->event.zoom -= (fractol->event.zoom * 0.05);
		fractol->event.mve_horiz += fractol->event.mouse_move_x * fractol->event.zoom * 0.05;
		fractol->event.mve_vertic += fractol->event.mouse_move_y * fractol->event.zoom * 0.05;
//		printf("fractol->event.mouse_move_x: %d\n", fractol->event.mouse_move_x);
//		printf("fractol->event.mouse_move_y; %d\n", fractol->event.mouse_move_y);
		fractol->event.plus_it -= 1;
	}
	else if (mousecode == 5 || mousecode == 2)
	{
		fractol->event.zoom += (fractol->event.zoom * 0.05);
		fractol->event.mve_horiz -= fractol->event.mouse_move_x * fractol->event.zoom * 0.05;
		fractol->event.mve_vertic -= fractol->event.mouse_move_y * fractol->event.zoom * 0.05;
		fractol->event.plus_it += 1;
//		printf("fractol->event.mouse_move_x: %d\n", fractol->event.mouse_move_x);
//		printf("fractol->event.mouse_move_y; %d\n", y);
	}
//	printf("x: %d\n", x);
//	printf("y; %d\n", y);
	run_cl(fractol);
}

void	mouse_move(int x, int y, void *param)
{
	t_fractol *fractol;

	fractol = (t_fractol*) param;
	if (x > WIDTH || y > HEIGHT || x < 0 || y < 0)
		return ;
	if (fractol->event.stop_jl != 0)
		return ;
//	if (fractol->event.stop_jl == 1)
//		return ;
	fractol->event.jl_move_x = (double)x * fractol->event.zoom;
	fractol->event.jl_move_y = (double)y * fractol->event.zoom;

//	printf("y: %d, x: %d\n", y, x);
//	fractol->event.mve_horiz = -((WIDTH / 2) * fractol->event.zoom) - x * fractol->event.zoom;
//	fractol->event.mve_vertic = -((HEIGHT / 2) * fractol->event.zoom) - y * fractol->event.zoom;
	run_cl(fractol);
}
//void 	jump_mandelbrot(int keycode, void * param)
//{
//	t_fractol *fractol;
//
//	fractol = (t_fractol *)param;
//	if (keycode == JUMP)
//		fractol->flg + 1 > 3 ? fractol->flg += 1 : fractol->flg == 0;
//}
