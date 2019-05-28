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
}					t_fractol;

int		ft_rgb_to_hex(int r, int g, int b)
{
	int res = 0;
	res = r << 16 | g << 8 | b;
	return (res);
}

put_pixel_img(int x, int y, __global int *image, int color)
{
	int WIDTH = 2560;
	int HEIGHT = 1315;
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
		image[x + WIDTH * y] = color;
}

__kernel void test(__global int *int_mem, __global double *double_mem, __global int *image)
{
//	printf("abc\n");
	int gid = get_global_id(0);
	t_fractol	data;
	int WIDTH = 2560;
	int HEIGHT = 1315;
	double tmp;

	data.x = gid % WIDTH;
	data.y = gid / WIDTH;
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

	data.mve_horiz = -((WIDTH / 2) * data.zoom) + data.horiz;
	data.mve_vertic =  -((HEIGHT / 2) * data.zoom) + data.vertic;
	data.c_r = data.x * data.zoom + data.mve_horiz;
	data.c_i = data.y * data.zoom + data.mve_vertic;
	data.z_i = 0;
	data.z_r = 0;
	data.it = -50 + data.plus_it;
	while (data.z_i * data.z_i + data.z_r * data.z_r <= 4 && data.it < data.it_max)
	{
		tmp = data.z_r;
		data.z_r = tmp * tmp - data.z_i * data.z_i + data.c_r;
		data.z_i = 2 * tmp * data.z_i + data.c_i;
		data.it++;
	}
	if (data.it >= data.it_max)
		put_pixel_img(data.x, data.y, image, 0x000000);
	else
		put_pixel_img(data.x, data.y, image, ft_rgb_to_hex(255 - 9 * data.it,  255 -  7 * data.it,  255 - 12 * data.it));
}