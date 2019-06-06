/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkeli <rkeli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 17:18:46 by rkeli             #+#    #+#             */
/*   Updated: 2019/06/05 22:19:15 by rkeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int				ft_close(void *param)
{
	t_fractol *fractol;

	fractol = (t_fractol*)param;
	close_cl(fractol);
	return (0);
}

static void		k_event(int keycode, t_fractol *fractol)
{
	if (keycode == UP)
		fractol->event.vertic += (fractol->event.zoom * 17);
	else if (keycode == DOWN)
		fractol->event.vertic -= (fractol->event.zoom * 17);
	else if (keycode == RIGHT)
		fractol->event.horiz -= (fractol->event.zoom * 17);
	else if (keycode == LEFT)
		fractol->event.horiz += (fractol->event.zoom * 17);
	else if (keycode == CHANGE_FRACTAL_U)
	{
		if (fractol->flg <= 4)
			(fractol->flg)++;
		else
			fractol->flg = 0;
		fractol_init(fractol);
		if (fractol->flg == 4)
		{
			fractol->event.mve_horiz = -1.675537;
			fractol->event.mve_vertic = -0.034484;
			fractol->event.zoom = 0.000039;
		}
	}
}

static void		ky_event(int keycode, t_fractol *fractol)
{
	if (keycode == CHANGE_FRACTAL_D)
	{
		if (fractol->flg > 0)
			(fractol->flg)--;
		else
			fractol->flg = 4;
		fractol_init(fractol);
		if (fractol->flg == 4)
		{
			fractol->event.mve_horiz = -1.675537;
			fractol->event.mve_vertic = -0.034484;
			fractol->event.zoom = 0.000039;
		}
	}
	else if (keycode == SPACE)
	{
		if (fractol->flg == 2)
		{
			if (fractol->event.stop_jl == 0)
				fractol->event.stop_jl = 1;
			else
				fractol->event.stop_jl = 0;
		}
	}
}

static void		zoom(int keycode, t_fractol *fractol)
{
	if (keycode == ZOOM_INTO)
	{
		fractol->event.zoom -= (fractol->event.zoom * 0.05);
		fractol->event.mve_horiz +=
				fractol->event.mouse_move_x * fractol->event.zoom * 0.05;
		fractol->event.mve_vertic +=
				fractol->event.mouse_move_y * fractol->event.zoom * 0.05;
		fractol->event.plus_it -= 1;
	}
	else if (keycode == ZOOM_OUT)
	{
		fractol->event.zoom += (fractol->event.zoom * 0.05);
		fractol->event.mve_horiz -=
				fractol->event.mouse_move_x * fractol->event.zoom * 0.05;
		fractol->event.mve_vertic -=
				fractol->event.mouse_move_y * fractol->event.zoom * 0.05;
		fractol->event.plus_it += 1;
	}
}

int				key_event(int keycode, void *param)
{
	t_fractol *fractol;

	fractol = (t_fractol *)param;
	keycode == ESC ? close_cl(fractol) : 1;
	k_event(keycode, fractol);
	ky_event(keycode, fractol);
	zoom(keycode, fractol);
	if (keycode == ITERATE_MUNIS)
		(fractol->event.it_max) - 10 == 0 ? 1 : (fractol->event.it_max -= 10);
	else if (keycode == ITERATE_PLUS)
		fractol->event.it_max += 10;
	else if (keycode == RESET)
	{
		fractol_init(fractol);
		if (fractol->flg == 4)
		{
			fractol->event.mve_horiz = -1.675537;
			fractol->event.mve_vertic = -0.034484;
			fractol->event.zoom = 0.000039;
		}
	}
	run_cl(fractol);
	return (0);
}
