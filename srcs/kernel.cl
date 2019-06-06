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
	if (data.it >= data.it_max)
		put_pixel_img(data, data.x, data.y, image, 0x000000);
	else
		put_pixel_img(data, data.x, data.y, image, ft_rgb_to_hex(255 - 13 * data.it * 0.7,  255 -  9 * data.it * 0.85,  255 - 4 * data.it));
}

/*
** Mandelbrot fractal
*/

void 		mandelbrot(t_fractol data, __global int *image)
{
	double tmp;

	data.c_r = data.x * data.zoom + data.mve_horiz + data.horiz;
	data.c_i = data.y * data.zoom + data.mve_vertic + data.vertic;
	data.z_i = 0;
	data.z_r = 0;
	data.it = -100 + data.plus_it;
	while (data.z_i * data.z_i + data.z_r * data.z_r <= 4 && data.it < data.it_max)
	{
		tmp = data.z_r;
		data.z_r = tmp * tmp - data.z_i * data.z_i + data.c_r;
		data.z_i = 2 * tmp * data.z_i + data.c_i;
		data.it++;
	}
	if (data.it >= data.it_max)
		put_pixel_img(data, data.x, data.y, image, 0x000000);
	else
		put_pixel_img(data, data.x, data.y, image, ft_rgb_to_hex(/*255 - */data.it * 0.007,  255 -  9 * data.it * 0.85,  255 - 4 * data.it));
}

void 		julia(t_fractol data, __global int *image)
{
	double	tmp;

	data.c_r = data.x * data.zoom + data.mve_horiz + data.horiz;
	data.c_i = data.y * data.zoom + data.mve_vertic + data.vertic;
	data.it = -200;
	while (data.c_i * data.c_i + data.c_r * data.c_r <= 4 && data.it < data.it_max)
	{
		tmp = data.c_i;
		data.c_i = data.c_i * data.c_i - data.c_r * data.c_r + data.jl_move_x;
		data.c_r = 2.0 * tmp * data.c_r + data.jl_move_y;
		data.it++;
	}
	if (data.it >= data.it_max)
		put_pixel_img(data, data.x, data.y, image, 0x000000);
	else
		put_pixel_img(data, data.x, data.y, image, ft_rgb_to_hex(255 - 13 * data.it * 0.005,  255 - 9 * data.it * 0.15,  255 - 4 * data.it));
}

static void	render(t_fractol data, __global int *image, int flg)
{
	if (flg == 1)
		mandelbrot(data, image);
	else if (flg == 2)
		julia(data, image);
	else if (flg == 3)
		carpet(data, image);
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
	render(data, image, flg);
}