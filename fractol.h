/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkeli <rkeli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 15:16:27 by rkeli             #+#    #+#             */
/*   Updated: 2019/06/03 22:36:55 by rkeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRCTOL_FRACTOL_H
#define FRCTOL_FRACTOL_H

# include "libft/libft.h"
# include "libft/get_next_line.h"
# include <mlx.h>
# include <math.h>
# include <stdlib.h>
#include <OpenCL/opencl.h>
//# include <stdio.h>
# include <complex.h>
# define HEIGHT 1315
# define WIDTH 2560
//# define HEIGHT 1000
//# define WIDTH 1000

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
	JUMP = 38,
	ITERATE_PLUS = 67,
	ITERATE_MUNIS = 75,
	SPACE = 49
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
	int				x;
	int				y;
	int				it;
	double			c_r;
	double			c_i;
	double			z_r;
	double			z_i;
}					t_fractol_calc;

typedef struct 		s_event
{
	int				mouse_move_x;
	int				mouse_move_y;
	int 			color;
	int 			it_max;
	int 			plus_it;
	int 			stop_jl;
	double 			zoom;
	double			mve_horiz;
	double 			mve_vertic;
	double 			horiz;
	double 			vertic;
	double 			jl_move_x;
	double 			jl_move_y;
}					t_event;

typedef struct		s_cl
{
	cl_context context;
	cl_command_queue queue;
	cl_platform_id platform_id;
	cl_uint ret_num_platforms;
	cl_uint ret_num_devices;
	cl_device_id device_id;
	cl_program program;
	cl_kernel	kernel;
	cl_mem		int_mem;
	cl_mem		double_mem;
	cl_mem 		mem_img;
}					t_cl;

typedef struct 		s_fractol
{
	t_img			img;
	t_fractol_calc	calc;
	t_event			event;
	t_cl			cl;
	void			*mlx;
	void			*win;
	int 			flg;
	int 			jflg;
}					t_fractol;

void			put_pixel_img(int x, int y, t_fractol *fractol, int color);
void			fractol_init(t_fractol *fractol);
void			img_init(t_fractol *fractol);
void			mandelbrot(t_fractol *fractol);
void			carpet(t_fractol *fractol);
void			burningship(t_fractol *fractol);
void			julia(t_fractol *fractol);
void			render(t_fractol *fractol);
int				ft_rgb_to_hex(int r, int g, int b);
int				ft_close(void *param);
int 			key_event(int keycode, void *param);
void 			mouse_event(int mousecode, int x, int y, void *param);
void			mouse_move(int x, int y, void *param);
void			create_cl(t_fractol *data);
void			run_cl(t_fractol *data);
//void			zoom_out(t_fractol *fractol, int x, int y);
//void			zoom_into(t_fractol *fractol, int x, int y);

#endif
