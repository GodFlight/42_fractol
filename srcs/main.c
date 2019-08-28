/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkeli <rkeli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 15:21:44 by rkeli             #+#    #+#             */
/*   Updated: 2019/08/28 02:57:24 by rkeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void			change_fractol(char *argv, t_fractol *fractol)
{
	fractol->flg = 0;
	if (!(ft_strcmp(argv, "mandelbrot")))
		fractol->flg = 1;
	else if (!(ft_strcmp(argv, "julia")))
		fractol->flg = 2;
	else if (!(ft_strcmp(argv, "manjulia")))
		fractol->flg = 3;
	else if (!(ft_strcmp(argv, "mandjuliaburn")))
		fractol->flg = 4;
	else if (!(ft_strcmp(argv, "burningship")))
	{
		fractol->flg = 5;
		fractol->event.mve_horiz = -1.675537;
		fractol->event.mve_vertic = -0.034484;
		fractol->event.zoom = 0.000039;
	}
	else
	{
		ft_putstr("usage: ./fractol target_name\n");
		ft_putstr("target_name: mandelbrot, julia, manjulia, mandjuliaburn, burningship\n");
		exit(32);
	}
}

void				img_init(t_fractol *fractol)
{
	fractol->img.img = mlx_new_image(fractol->mlx, WIDTH, HEIGHT);
	fractol->img.data = (int*)mlx_get_data_addr(fractol->img.img,
			&fractol->img.bpp, &fractol->img.line_size, &fractol->img.endian);
	fractol->img.bpp /= 8;

}

void				fractol_init(t_fractol *fractol)
{
	fractol->event.it_max = 50;
	fractol->event.stop_jl = 1;
	fractol->event.zoom = 0.002;
	fractol->event.vertic = 0;
	fractol->event.horiz = 0;
	fractol->event.mouse_move_x = 0;
	fractol->event.mouse_move_y = 0;
	fractol->event.mve_horiz = -((WIDTH / 2) * fractol->event.zoom)
													+ fractol->event.horiz;
	fractol->event.mve_vertic = -((HEIGHT / 2) * fractol->event.zoom)
													+ fractol->event.vertic;
	fractol->event.jl_move_x = 0.218000;
	fractol->event.jl_move_y = 0.546000;
	fractol->event.plus_it = 0;
	fractol->calc.z_i = 0;
	fractol->calc.z_r = 0;
	fractol->calc.c_i = 0;
	fractol->calc.c_i = 0;
	fractol->str_color = 0xFFFFFF;
	fractol->event.r = -3.617692;
	fractol->event.g = -4.471539;
	fractol->event.b = -11.271538;
}

int					main(int argc, char **argv)
{
	t_fractol *fractol;

	if (argc == 1 && argv)
	{
		ft_putstr("usage: ./fractol target_name\n");
		ft_putstr("target_name: mandelbrot, julia, manjulia, mandjuliaburn, " \
			"burningship\n");
		exit(32);
	}
	if (!(fractol = malloc(sizeof(t_fractol))))
		exit(30);
	change_fractol(argv[1], fractol);
	fractol_init(fractol);
	fractol->mlx = mlx_init();
	img_init(fractol);
	fractol->win = mlx_new_window(fractol->mlx, WIDTH, HEIGHT, "Fractol");
	create_cl(fractol);
	run_cl(fractol);
	mlx_hook(fractol->win, 17, 0, &ft_close, fractol);
	mlx_hook(fractol->win, 2, 0, &key_event, fractol);
	mlx_hook(fractol->win, 4, 0, &mouse_event, fractol);
	mlx_hook(fractol->win, 6, 0, &mouse_move, fractol);
	string_output(fractol);
	mlx_loop(fractol->mlx);
	return (0);
}
