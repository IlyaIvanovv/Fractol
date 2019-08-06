/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readinit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arunte <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 16:40:58 by arunte            #+#    #+#             */
/*   Updated: 2019/05/25 18:04:30 by arunte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		draw_img(void *mlx, void *win, t_img img)
{
	return (mlx_put_image_to_window(mlx, win, img.img_ptr, 0, 0));
}

void	put_pix_img(t_map *ftol, int x, int y, unsigned int color)
{
	if (ftol->x < SIZE && ftol->y < SIZE)
	{
		ftol->img.data[y * SIZE + x] = color;
	}
}

void	redraw(t_map *ftol)
{
	ftol->img.img_ptr = mlx_new_image(ftol->window.mlx_ptr, SIZE, SIZE);
	ftol->img.data = (unsigned int *)mlx_get_data_addr(ftol->img.img_ptr,
			&ftol->img.bits_per_pixel,
			&ftol->img.size_line,
			&ftol->img.end);
	draw_ftol(ftol);
	draw_img(ftol->window.mlx_ptr, ftol->window.win_ptr, ftol->img);
}

void	zoomin(int keys, int x, int y, t_map *ftol)
{
	double past_x;
	double past_y;

	if (keys == 4)
	{
		past_x = (x / ftol->zoom + ftol->x1);
		past_y = (y / ftol->zoom + ftol->y1);
		ftol->zoom *= 1.3;
		ftol->x1 = past_x - (x / ftol->zoom);
		ftol->y1 = past_y - (y / ftol->zoom);
		redraw(ftol);
	}
}

void	zoomout(int keys, int x, int y, t_map *ftol)
{
	double past_x;
	double past_y;

	if (keys == 5)
	{
		past_x = (x / ftol->zoom + ftol->x1);
		past_y = (y / ftol->zoom + ftol->y1);
		ftol->zoom /= 1.3;
		ftol->x1 = past_x - (x / ftol->zoom);
		ftol->y1 = past_y - (y / ftol->zoom);
		redraw(ftol);
	}
}
