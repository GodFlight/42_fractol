/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkeli <rkeli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 15:16:27 by rkeli             #+#    #+#             */
/*   Updated: 2019/05/25 14:14:04 by rkeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRCTOL_FRACTOL_H
#define FRCTOL_FRACTOL_H

# include "libft/libft.h"
# include <mlx.h>
# include <math.h>
# include <stdlib.h>
//# include <stdio.h>
# include <complex.h>
# define DEG2RAD M_PI / 180
# define HEIGHT 1315
# define WIDTH 2560

typedef enum
{
	ESC = 53,
	ZOOM_INTO = 69,
	ZOOM_OUT = 78,
	UP = 126,
	DOWN = 125,
	RIGHT = 124,
	LEFT = 123,
	ROTATE_UP = 91,
	ROTATE_DOWN = 84,
	ROTATE_RIGHT = 88,
	ROTATE_LEFT = 86,
	ROTATE = 65,
	RESET = 15,
	ITERATE_PLUS = 67,
	ITERATE_MUNIS = 75
}	t_keycode;

typedef struct		s_img
{
	void			*img;
	int				*data;
	int				bpp;
	int				endian;
	int				line_size;
}					t_img;

typedef struct 		s_fractol_calc
{
	int			x;
	int			y;
	int			it;
	double		c_r;
	double		c_i;
	double		z_r;
	double		z_i;
}					t_fractol_calc;

typedef struct 		s_event
{
	double			mouse_move;
	double 			zoom;
	int 			color;
	int 			it_max;
}					t_event;

typedef struct 		s_fractol
{
	t_img			img;
	t_fractol_calc	calc;
	t_event			event;
	void			*mlx;
	void			*win;
}					t_fractol;

void			put_pixel_img(int x, int y, t_fractol *fractol, int color);
void			fractol_init(t_fractol *fractol);
void			img_init(t_fractol *fractol);
void			mandelbrot(t_fractol *fractol);
void			julia(t_fractol *fractol);
void			burningship_calc(t_fractol *fractol);
void			mandelbrot_calc(t_fractol *fractol);
void			carpet_calc(t_fractol *fractol);
int				ft_rgb_to_hex(int r, int g, int b);
int				ft_close(void *param);
int 			key_event(int keycode, void *param);
int 			mouse_move_event(int mousecode, int x, int y, t_fractol *fractol);

#endif
