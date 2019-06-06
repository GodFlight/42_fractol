/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_costl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkeli <rkeli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 18:07:00 by rkeli             #+#    #+#             */
/*   Updated: 2019/06/06 22:31:40 by rkeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void		m_event(int mousecode, t_fractol *fractol)
{
	if (mousecode == 4 || mousecode == 1)
	{
		fractol->event.zoom -= (fractol->event.zoom * 0.05);
		fractol->event.mve_horiz += fractol->event.mouse_move_x
				* fractol->event.zoom * 0.05;
		fractol->event.mve_vertic += fractol->event.mouse_move_y
				* fractol->event.zoom * 0.05;
		fractol->event.plus_it -= 1;
	}
	else if (mousecode == 5 || mousecode == 2)
	{
		fractol->event.zoom += (fractol->event.zoom * 0.05);
		fractol->event.mve_horiz -= fractol->event.mouse_move_x
				* fractol->event.zoom * 0.05;
		fractol->event.mve_vertic -= fractol->event.mouse_move_y
				* fractol->event.zoom * 0.05;
		fractol->event.plus_it += 1;
	}
}

int				mouse_event(int mousecode, int x, int y, void *param)
{
	t_fractol	*fractol;

	fractol = (t_fractol *)param;
	if (x > WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return (0);
	fractol->event.mouse_move_x = x;
	fractol->event.mouse_move_y = y;
	m_event(mousecode, fractol);
	run_cl(fractol);
	return (0);
}

int				mouse_move(int x, int y, void *param)
{
	t_fractol	*fractol;

	fractol = (t_fractol*)param;
	if (x > WIDTH || y > HEIGHT || x < 0 || y < 0)
		return (0);
	if (fractol->event.stop_jl != 0)
		return (0);
	fractol->event.jl_move_x = (double)x * fractol->event.zoom;
	fractol->event.jl_move_y = (double)y * fractol->event.zoom;
	run_cl(fractol);
	return (0);
}
