/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kernel.cl                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkeli <rkeli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 13:38:22 by rkeli             #+#    #+#             */
/*   Updated: 2019/06/06 13:38:22 by rkeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


typedef struct		s_fractol
{
	int 			WIDTH;
	int 			HEIGHT;
	int				x;
	int				y;
	int				it;
	int 			color;
	int 			it_max;
	int 			plus_it;
	double			c_r;
	double			c_i;
	double			z_r;
	double			z_i;
	double 			zoom;
	double			mve_horiz;
	double 			mve_vertic;
	double 			horiz;
	double 			vertic;
	double 			jl_move_x;
	double 			jl_move_y;
	double3			rgb;
}					t_fractol;

int			ft_rgb_to_hex(int r, int g, int b)
{
	int		res = 0;
	int		alpha = 0;

	alpha |= 16777215;
	res = r << 16 | g << 8 | b;
	res &= alpha;
	return (res);
}

void		put_pixel_img(t_fractol data, int x, int y, __global int *image, int color)
{
	if (x >= 0 && x < data.WIDTH && y >= 0 && y < data.HEIGHT)
		image[x + data.WIDTH * y] = color;
}

/*
**	Carpet fractal
*/

void		carpet(t_fractol data, __global int *image)
{
	int		i;

	i = 0;
	data.it = 0;
	int x = data.x * data.zoom + data.mve_horiz + data.horiz;
	int y = data.y * data.zoom + data.mve_vertic + data.vertic;
	x = abs(x);
	y = abs(y);
	while ((x > 0 || y > 0) && i < data.it < data.it_max)
	{
		if (x % 3 == 1 && y % 3 == 1)
			break;
		x /= 3;
		y /= 3;
		data.it++;
	}
	if (data.it >= data.it_max)
		put_pixel_img(data, data.x, data.y, image, 0x000000);
	else
		put_pixel_img(data, data.x, data.y, image, ft_rgb_to_hex(255 - 13 * data.it,  255 -  9 * data.it,  255 - 4 * data.it));
}

/*
**	Burningship fractal
*/

void 		burningship(t_fractol data, __global int *image)
{
	double tmp;
	double z_r;
	double z_i;
	double x;

	data.c_r = data.x * data.zoom + data.mve_horiz + data.horiz;
	data.c_i = data.y * data.zoom + data.mve_vertic + data.vertic;
	data.it = -100 + data.plus_it;
	z_r = 0;
	z_i = 0;
	while (z_i * z_i + z_r * z_r <= 4  && data.it < data.it_max)
	{
		tmp = z_r;
		z_r = fabs(tmp * tmp) - z_i * z_i + data.c_r;
		z_i = 2 * fabs(tmp * z_i) + data.c_i;
		data.it++;
	}
	if(z_i * z_i + z_r * z_r != 1)
		x = (double)data.it - log2(log2(z_r * z_r + z_i * z_i)) + 4.0;
	else
		x = (double)data.it + 4.0;
	double3 bla = 256 * (0.5 + 0.5 * cos((3.0 + x * 0.15 + (double3){data.rgb.x, data.rgb.y, data.rgb.z})));
	if (data.it >= data.it_max)
		put_pixel_img(data, data.x, data.y, image, 0x000000);
	else
		put_pixel_img(data, data.x, data.y, image, (((int) (bla.x)) << 16) | ((int) (bla.y)) << 8 | ((int) (bla.z)));
}

/*
** Mandelbrot + julia set
*/

void 		m_j_set(t_fractol data, __global int *image)
{
	double	tmp;
	double 	x;

	data.c_r = data.x * data.zoom + data.mve_horiz + data.horiz;
	data.c_i = data.y * data.zoom + data.mve_vertic + data.vertic;
	data.z_i = 0;
	data.z_r = 0;
	data.it = -100;
	while (data.z_i * data.z_i + data.z_r * data.z_r <= 256 && data.it < data.it_max)
	{
		tmp = data.z_r;
		data.z_r = tmp * tmp - data.z_i * data.z_i + data.c_r;
		data.z_i = 2 * tmp * data.z_i + data.c_i;
		tmp = data.c_i;
		data.c_i = data.c_i * data.c_i - data.c_r * data.c_r + data.jl_move_x;
		data.c_r = 2.0 * tmp * data.c_r + data.jl_move_y;
		data.it++;
	}
	if(data.z_i * data.z_i + data.z_r * data.z_r != 1)
		x = (double)data.it - log2(log2(data.z_r * data.z_r + data.z_i * data.z_i)) + 4.0;
	else
		x = (double)data.it + 4.0;
	double3 bla = 256 * (0.5 + 0.5 * cos((3.0 + x * 0.15 + (double3){data.rgb.x, data.rgb.y, data.rgb.z})));
	if (data.it >= data.it_max)
		put_pixel_img(data, data.x, data.y, image, 0x000000);
	else
		put_pixel_img(data, data.x, data.y, image, (((int) (bla.x)) << 16) | ((int) (bla.y)) << 8 | ((int) (bla.z)));
}

/*
**	Mandelbrot + julia + burningship set
*/

void 		m_j_b_set(t_fractol data, __global int *image)
{
	double	tmp;
	double 	x;

	data.c_r = data.x * data.zoom + data.mve_horiz + data.horiz;
	data.c_i = data.y * data.zoom + data.mve_vertic + data.vertic;
	data.z_i = 0;
	data.z_r = 0;
	data.it = -100;
	while (data.z_i * data.z_i + data.z_r * data.z_r <= 256 && data.it < data.it_max)
	{
		tmp = data.z_r;
		data.z_r = tmp * tmp - data.z_i * data.z_i + data.c_r;
		data.z_i = 2 * tmp * data.z_i + data.c_i;
		tmp = data.c_i;
		data.c_i = data.c_i * data.c_i - data.c_r * data.c_r + data.jl_move_x;
		data.c_r = 2.0 * tmp * data.c_r + data.jl_move_y;
		tmp = data.z_r;
		data.z_r = fabs(tmp * tmp) - data.z_i * data.z_i + data.c_r;
		data.z_i = 2 * fabs(tmp * data.z_i) + data.c_i;
		data.it++;
	}
	if(data.z_i * data.z_i + data.z_r * data.z_r != 1)
		x = (double)data.it - log2(log2(data.z_r * data.z_r + data.z_i * data.z_i)) + 4.0;
	else
		x = (double)data.it + 4.0;
	double3 bla = 256 * (0.5 + 0.5 * cos((3.0 + x * 0.15 + (double3){data.rgb.x, data.rgb.y, data.rgb.z})));
	if (data.it >= data.it_max)
		put_pixel_img(data, data.x, data.y, image, 0x000000);
	else
		put_pixel_img(data, data.x, data.y, image, (((int) (bla.x)) << 16) | ((int) (bla.y)) << 8 | ((int) (bla.z)));
}

/*
** Mandelbrot fractal
*/

void 		mandelbrot(t_fractol data, __global int *image)
{
	double	tmp;
	double 	x;

	data.c_r = data.x * data.zoom + data.mve_horiz + data.horiz;
	data.c_i = data.y * data.zoom + data.mve_vertic + data.vertic;
	data.z_i = 0;
	data.z_r = 0;
	data.it = -100;
	while (data.z_i * data.z_i + data.z_r * data.z_r <= 256 && data.it < data.it_max)
	{
		tmp = data.z_r;
		data.z_r = tmp * tmp - data.z_i * data.z_i + data.c_r;
		data.z_i = 2 * tmp * data.z_i + data.c_i;
		data.it++;
	}
	if(data.z_i * data.z_i + data.z_r * data.z_r != 1)
		x = (double)data.it - log2(log2(data.z_r * data.z_r + data.z_i * data.z_i)) + 4.0;
	else
		x = (double)data.it + 4.0;
	double3 bla = 256 * (0.5 + 0.5 * cos((3.0 + x * 0.15 + (double3){data.rgb.x, data.rgb.y, data.rgb.z})));
	if (data.it >= data.it_max)
		put_pixel_img(data, data.x, data.y, image, 0x000000);
	else
		put_pixel_img(data, data.x, data.y, image, (((int) (bla.x)) << 16) | ((int) (bla.y)) << 8 | ((int) (bla.z)));
}

void 		julia(t_fractol data, __global int *image)
{
	double	tmp;
	double	x;
	double z_r;
	double z_i;

	data.c_r = data.x * data.zoom + data.mve_horiz + data.horiz;
	data.c_i = data.y * data.zoom + data.mve_vertic + data.vertic;
	z_r = 0;
	z_i = 0;
	data.it = -200;
	while (data.c_i * data.c_i + data.c_r * data.c_r <= 4 && data.it < data.it_max)
	{
		tmp = data.c_i;
		data.c_i = data.c_i * data.c_i - data.c_r * data.c_r + data.jl_move_x;
		data.c_r = 2.0 * tmp * data.c_r + data.jl_move_y;
		data.it++;
	}
	if(data.c_i * data.c_i + data.c_r * data.c_r != 1)
		x = (double)data.it - log2(log2(data.c_r * data.c_r + data.c_i * data.c_i)) + 4.0;
	else
		x = (double)data.it + 4.0;
	double3 bla = 256 * (0.5 + 0.5 * cos((3.0 + x * 0.15 + (double3){data.rgb.x, data.rgb.y, data.rgb.z})));
	if (data.it >= data.it_max)
		put_pixel_img(data, data.x, data.y, image, 0x000000);
	else
		put_pixel_img(data, data.x, data.y, image, (((int) (bla.x)) << 16) | ((int) (bla.y)) << 8 | ((int) (bla.z)));
}

static void	render(t_fractol data, __global int *image, int flg)
{
	if (flg == 1)
		mandelbrot(data, image);
	else if (flg == 2)
		julia(data, image);
	else if (flg == 3)
		m_j_set(data, image);
	else if (flg == 4)
		m_j_b_set(data, image);
	else
		burningship(data, image);
}

__kernel void	test(__global int *int_mem, __global double *double_mem, __global int *image)
{
	t_fractol	data;
	int 		gid;
	int 		flg;

	gid = get_global_id(0);
	flg = int_mem[7];
	data.WIDTH = int_mem[5];
	data.HEIGHT = int_mem[6];
	data.x = gid % data.WIDTH;
	data.y = gid / data.WIDTH;
	data.it = int_mem[2];
	data.it_max = int_mem[3];
	data.plus_it = int_mem[4];
	data.c_r = double_mem[0];
	data.c_i = double_mem[1];
	data.z_r = double_mem[2];
	data.z_i = double_mem[3];
	data.mve_horiz = double_mem[4];
	data.mve_vertic = double_mem[5];
	data.zoom = double_mem[6];
	data.horiz = double_mem[7];
	data.vertic = double_mem[8];
	data.jl_move_x = double_mem[9];
	data.jl_move_y = double_mem[10];
	data.rgb = (double3){double_mem[11], double_mem[12], double_mem[13]};
	render(data, image, flg);
}