/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cl                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkeli <rkeli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 22:35:57 by rkeli             #+#    #+#             */
/*   Updated: 2019/05/28 22:35:57 by rkeli            ###   ########.fr       */
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
//	int WIDTH = 2560;
//	int HEIGHT = 1315;
	if (x >= 0 && x < data.WIDTH && y >= 0 && y < data.HEIGHT)
		image[x + data.WIDTH * y] = color;
//	printf("color: %d\n", color >> 24);
}

void 		burningship(t_fractol data, __global int *image)
{
	double tmp;
	double z_r;
	double z_i;

	data.c_r = data.x * data.zoom + data.mve_horiz;
	data.c_i = data.y * data.zoom + data.mve_vertic;
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
		put_pixel_img(data, data.x, data.y, image, ft_rgb_to_hex(255 - 13 * data.it,  255 -  9 * data.it,  255 - 4 * data.it));
}

void 		mandelbrot(t_fractol data, __global int *image)
{
	double tmp;

	data.c_r = data.x * data.zoom + data.mve_horiz;
	data.c_i = data.y * data.zoom + data.mve_vertic;
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
		put_pixel_img(data, data.x, data.y, image, ft_rgb_to_hex(255 - 13 * data.it,  255 -  9 * data.it,  255 - 4 * data.it));
}

void 		julia(t_fractol data, __global int *image)
{
//	int		WIDTH = 2560;
//	int 	HEIGHT = 1315;
	double	tmp;

	data.c_r = data.x * data.zoom + -((data.WIDTH / 2) * data.zoom) + data.horiz;
	data.c_i = data.y * data.zoom + -((data.HEIGHT / 2) * data.zoom) + data.vertic;
	data.it = -100 + data.plus_it;
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
		put_pixel_img(data, data.x, data.y, image, ft_rgb_to_hex(255 - 13 * data.it,  255 -  9 * data.it,  255 - 4 * data.it));
}

__kernel void	test(__global int *int_mem, __global double *double_mem, __global int *image)
{
	t_fractol	data;
	int			gid = get_global_id(0);
//	int			WIDTH = 2560;
//	int			HEIGHT = 1315;
	double		tmp;

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

//	mandelbrot(data, image);
//	julia(data, image);
	burningship(data, image);
//	data.zoom = 0.0000000000032;
	//data.mve_horiz = 0.777807810193171;
	//data..mve_vertic = 0.131645108003206;
//	data.c_r = data.x * data.zoom + data.mve_horiz;
//	data.c_i = data.y * data.zoom + data.mve_vertic;
//	data.z_i = 0;
//	data.z_r = 0;
//	data.it = -100 + data.plus_it;
//	while (data.z_i * data.z_i + data.z_r * data.z_r <= 4 && data.it < data.it_max)
//	{
//		tmp = data.z_r;
//		data.z_r = tmp * tmp - data.z_i * data.z_i + data.c_r;
//		data.z_i = 2 * tmp * data.z_i + data.c_i;
//		data.it++;
//	}
//	if (data.it >= data.it_max)
//		put_pixel_img(data, data.x, data.y, image, 0x000000);
//	else
//		put_pixel_img(data, data.x, data.y, image, ft_rgb_to_hex(255 - 13 * data.it,  255 -  9 * data.it,  255 - 4 * data.it));
//	if (data.it >= data.it_max)
//		put_pixel_img(data.x, data.y, image, 0x000000);
//	else
//		put_pixel_img(data.x, data.y, image, ft_rgb_to_hex(255 - 13 * data.it,  255 -  9 * data.it,  255 - 4 * data.it));
}