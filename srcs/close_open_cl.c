/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_open_cl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkeli <rkeli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 19:18:22 by rkeli             #+#    #+#             */
/*   Updated: 2019/06/06 14:23:40 by rkeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	close_cl(t_fractol *fractol)
{
	int ret;

	ret = 0;
	ret += clFinish(fractol->cl.queue);
	ret += clFlush(fractol->cl.queue);
	ret += clReleaseMemObject(fractol->cl.int_mem);
	ret += clReleaseMemObject(fractol->cl.double_mem);
	ret += clReleaseMemObject(fractol->cl.mem_img);
	ret += clReleaseKernel(fractol->cl.kernel);
	ret += clReleaseProgram(fractol->cl.program);
	ret += clReleaseCommandQueue(fractol->cl.queue);
	ret += clReleaseContext(fractol->cl.context);
	ret += clReleaseDevice(fractol->cl.device_id);
	exit(0);
}
