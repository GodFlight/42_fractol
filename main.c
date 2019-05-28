/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkeli <rkeli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 15:21:44 by rkeli             #+#    #+#             */
/*   Updated: 2019/05/27 21:43:52 by rkeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void		change_fractol(char *argv, t_fractol *fractol)
{
	fractol->flg = 0;
	if (!(ft_strcmp(argv, "mandelbrot")))
		fractol->flg = 1;
	else if (!(ft_strcmp(argv, "julia")))
		fractol->flg = 2;
	else if (!(ft_strcmp(argv, "carpet")))
		fractol->flg = 3;
	else if (!(ft_strcmp(argv, "burningship")))
		fractol->flg = 4;
	else
	{
		ft_putstr("usage: ./fractol target_name\n");
		ft_putstr("Available: ""mandelbrot"", ""julia"", ""carpet"", ""burningship""\n");
		exit (32);
	}
}

void			put_pixel_img(int x, int y, t_fractol *fractol, int color)
{
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
		fractol->img.data[x + y * WIDTH] = color;
}

void			img_init(t_fractol *fractol)
{
	fractol->img.img = mlx_new_image(fractol->mlx, WIDTH, HEIGHT);
	fractol->img.data = (int*)mlx_get_data_addr(fractol->img.img,
			&fractol->img.bpp, &fractol->img.line_size, &fractol->img.endian);
	fractol->img.bpp /= 8;
}

void	fractol_init(t_fractol *fractol)
{
	fractol->event.it_max = 50;
	fractol->event.zoom = 0.5;
	fractol->jflg = 0;
	fractol->event.vertic = 0;
	fractol->event.horiz = 0;
//	fractol->event.mve_horiz = -((WIDTH / 2) * fractol->event.zoom) + fractol->event.horiz;
//	fractol->event.mve_vertic = -((HEIGHT / 2) * fractol->event.zoom) + fractol->event.vertic;
	fractol->event.color = 3;
	fractol->event.plus_it = 0;
	fractol->mlx = mlx_init();
	fractol->win = mlx_new_window(fractol->mlx, WIDTH, HEIGHT, "Fractol");
}

int		main(int argc, char **argv)
{
	t_fractol *fractol;

	if (argc == 1)
		return 0;
	fractol = NULL;
	if (!(fractol = malloc(sizeof(t_fractol))))
		exit (30);
	change_fractol(argv[1], fractol);
	fractol_init(fractol);
	img_init(fractol);
	render(fractol);
	//mandelbrot(fractol);
	//mlx_hook(fractol->win, 12, 0 ,&mouse_move_event, fractol);
	mlx_hook(fractol->win, 17 , 0, &ft_close, NULL);
	mlx_hook(fractol->win, 2, 0, &key_event, fractol);
	mlx_mouse_hook(fractol->win, &mouse_move_event, fractol);
	mlx_loop(fractol->mlx);
	return (0);
}