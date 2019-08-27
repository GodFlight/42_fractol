/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkeli <rkeli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 17:18:46 by rkeli             #+#    #+#             */
/*   Updated: 2019/08/27 20:03:25 by rkeli            ###   ########.fr       */
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

static void		key_press_event(int keycode, t_fractol *fractol)
{
	if (keycode == UP)
		fractol->event.vertic += (fractol->event.zoom * 17);
	else if (keycode == DOWN)
		fractol->event.vertic -= (fractol->event.zoom * 17);
	else if (keycode == RIGHT)
		fractol->event.horiz -= (fractol->event.zoom * 17);
	else if (keycode == LEFT)
		fractol->event.horiz += (fractol->event.zoom * 17);
	else if (keycode == SPACE)
	{
		if (fractol->flg == 2 || fractol->flg == 3 || fractol->flg == 4)
		{
			if (fractol->event.stop_jl == 0)
				fractol->event.stop_jl = 1;
			else
				fractol->event.stop_jl = 0;
		}
	}
}

static void		init_conf_fractal(t_fractol *fractol, double r, double g,
				double b, double move_x, double move_y)
{
	fractol->event.r = r;
	fractol->event.g = g;
	fractol->event.b = b;
	fractol->event.jl_move_x = move_x;
	fractol->event.jl_move_y = move_y;
}

static void		change_fractal_event(int keycode, t_fractol *fractol)
{
	if (keycode == CHANGE_FRACTAL_D)
	{
		fractol->flg = (fractol->flg > 0 ? fractol->flg - 1 : 5);
		fractol_init(fractol);
		if (fractol->flg == 2)
			init_conf_fractal(fractol, 3.682308, 4.428461, -0.571538,
					0.218000, 0.546000);
		else if (fractol->flg == 3)
			init_conf_fractal(fractol, 15.682308, 1.528461, -5.471538,
							  0.254000, 0.278000);
		else if (fractol->flg == 4)
			init_conf_fractal(fractol, 2.682308, -4.471539, -2.928462,
							  0.344000, 0.074000);
		else if (fractol->flg == 5)
		{
			init_conf_fractal(fractol, 0.382308, -5.271539, -5.271538,
							  0, 0);
			fractol->event.mve_horiz = -1.675537;
			fractol->event.mve_vertic = -0.034484;
			fractol->event.zoom = 0.000039;
		}
	}
	else if (keycode == CHANGE_FRACTAL_U)
	{
		fractol->flg = (fractol->flg < 5 ? fractol->flg + 1 : 0);
		fractol_init(fractol);
		if (fractol->flg == 2)
			init_conf_fractal(fractol, 3.682308, 4.428461, -0.571538,
							  0.218000, 0.546000);
		else if (fractol->flg == 3)
			init_conf_fractal(fractol, 15.682308, 1.528461, -5.471538,
							  0.254000, 0.278000);
		else if (fractol->flg == 4)
			init_conf_fractal(fractol, 2.682308, -4.471539, -2.928462,
							  0.344000, 0.074000);
		else if (fractol->flg == 5)
		{
			init_conf_fractal(fractol, 0.382308, -5.271539, -5.271538,
							  0, 0);
			fractol->event.mve_horiz = -1.675537;
			fractol->event.mve_vertic = -0.034484;
			fractol->event.zoom = 0.000039;
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

static void		change_color_event(int keycode, t_fractol *fractol)
{
	if (keycode == RED_CHANEL_INCREMENT)
		fractol->event.r += 0.1;
	else if (keycode == GREEN_CHANEL_INCREMENT)
		fractol->event.g += 0.1;
	else if (keycode == BLUE_CHANEL_INCREMENT)
		fractol->event.b += 0.1;
	else if (keycode == RED_CHANEL_DECREMENT)
		fractol->event.r -= 0.1;
	else if (keycode == GREEN_CHANEL_DECREMENT)
		fractol->event.g -= 0.1;
	else if (keycode == BLUE_CHANEL_DECREMENT)
		fractol->event.b -= 0.1;
}


int				key_event(int keycode, void *param)
{
	t_fractol *fractol;

	fractol = (t_fractol *)param;
	keycode == ESC ? close_cl(fractol) : 1;
	key_press_event(keycode, fractol);
	change_fractal_event(keycode, fractol);
	zoom(keycode, fractol);
	change_color_event(keycode, fractol);
	if (keycode == ITERATE_MUNIS)
		(fractol->event.it_max) - 10 == 0 ? 1 : (fractol->event.it_max -= 10);
	else if (keycode == ITERATE_PLUS)
		fractol->event.it_max += 10;
	else if (keycode == RESET)
	{
		fractol_init(fractol);
		if (fractol->flg == 5)
		{
			init_conf_fractal(fractol, 0.382308, -5.271539, -5.271538,
					0, 0);
			fractol->event.mve_horiz = -1.675537;
			fractol->event.mve_vertic = -0.034484;
			fractol->event.zoom = 0.000039;
		}
	}
	run_cl(fractol);
	return (0);
}
