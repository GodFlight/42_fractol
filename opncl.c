/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opncl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkeli <rkeli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 19:16:58 by rkeli             #+#    #+#             */
/*   Updated: 2019/06/03 15:58:59 by rkeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

char	*read__file(char *path)
{
	int		fd;
	char	*line;
	char	*res;
	char	*old_res;

	res = ft_strnew(1);
	line = NULL;
	fd = open(path, O_RDONLY);
	if (fd < 2)
		exit(99);
	while (get_next_line(fd, &line))
	{
		old_res = res;
		res = ft_strjoin(res, line);
		free(old_res);
		old_res = res;
		res = ft_strjoin(res, "\n");
		free(old_res);
	}
	close(fd);
	return (res);
}

void		run_cl(t_fractol *data)
{
	size_t kernel_num;
	int mem[32];
	int ret;
	double dmem[32];

	kernel_num = WIDTH * HEIGHT;
	mem[5] = WIDTH;
	mem[6] = HEIGHT;
	mem[0] = data->calc.x;
	mem[1] = data->calc.y;
	mem[2] = data->calc.it;
	mem[3] = data->event.it_max;
	mem[4] = data->event.plus_it;
	dmem[0] = data->calc.c_r;
	dmem[1] = data->calc.c_i;
	dmem[2] = data->calc.z_r;
	dmem[3] = data->calc.z_i;
	dmem[4] = data->event.mve_horiz;
//	dmem[4] = -((WIDTH / 2) * data->event.zoom) + data->event.horiz;
	dmem[5] = data->event.mve_vertic;
//	dmem[5] =  -((HEIGHT / 2) * data->event.zoom) + data->event.vertic;
	dmem[6] = data->event.zoom;
	dmem[7] = data->event.horiz;
	dmem[8] = data->event.vertic;
	dmem[9] = data->event.jl_move_x;
	dmem[10] = data->event.jl_move_y;

	ret = clEnqueueWriteBuffer(data->cl.queue, data->cl.int_mem, CL_TRUE, 0, sizeof(int) * 32, mem, 0, NULL, NULL);
	ret = clEnqueueWriteBuffer(data->cl.queue, data->cl.double_mem, CL_TRUE, 0, sizeof(double) * 32, dmem, 0, NULL, NULL);
	ret = clEnqueueNDRangeKernel(data->cl.queue, data->cl.kernel, 1, NULL, &kernel_num, NULL, 0, NULL, NULL);
	ret = clEnqueueReadBuffer(data->cl.queue, data->cl.mem_img, CL_TRUE, 0, sizeof(int) * WIDTH * HEIGHT, data->img.data, 0, NULL, NULL);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
//	ret = clEnqueueReadBuffer(command_queue, memobj, CL_TRUE, 0, memLenth * sizeof(float), mem, 0, NULL, NULL);
}

void		create_cl(t_fractol *data)
{
	int ret;
	char *kernel_str;
	size_t kernel_len;

	ret = clGetPlatformIDs(1, &data->cl.platform_id, &data->cl.ret_num_platforms);
	ret = clGetDeviceIDs(data->cl.platform_id, CL_DEVICE_TYPE_GPU, 1, &data->cl.device_id, &data->cl.ret_num_devices);
	data->cl.context = clCreateContext(NULL, 1, &data->cl.device_id, NULL, NULL, &ret);
	data->cl.queue = clCreateCommandQueue(data->cl.context, data->cl.device_id, 0, &ret);
	kernel_str = read__file("./test.cl");
	kernel_len = ft_strlen(kernel_str);
	data->cl.program = clCreateProgramWithSource(data->cl.context, 1, (const char**)&kernel_str, &kernel_len, &ret);
	ret = clBuildProgram(data->cl.program, 1, &data->cl.device_id, NULL, NULL, NULL);
	data->cl.kernel = clCreateKernel(data->cl.program, "test", &ret);
	data->cl.int_mem = clCreateBuffer(data->cl.context, CL_MEM_READ_WRITE, sizeof(int) * 32, NULL, &ret);
	data->cl.mem_img = clCreateBuffer(data->cl.context, CL_MEM_READ_WRITE, sizeof(int) * WIDTH * HEIGHT, NULL, &ret);
	data->cl.double_mem = clCreateBuffer(data->cl.context, CL_MEM_READ_WRITE, sizeof(double) * 32, NULL, &ret);
	ret = clSetKernelArg(data->cl.kernel, 0, sizeof(cl_mem), &data->cl.int_mem);
	ret = clSetKernelArg(data->cl.kernel, 1, sizeof(cl_mem), &data->cl.double_mem);
	ret = clSetKernelArg(data->cl.kernel, 2, sizeof(cl_mem), &data->cl.mem_img);
}