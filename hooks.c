/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arunte <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 17:54:03 by arunte            #+#    #+#             */
/*   Updated: 2019/05/25 17:55:08 by arunte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	key_pressed(int keys, t_map *ftol)
{
	if (keys == 123)
		ftol->x1 -= 30 / ftol->zoom;
	else if (keys == 124)
		ftol->x1 += 30 / ftol->zoom;
	else if (keys == 126)
		ftol->y1 -= 30 / ftol->zoom;
	else if (keys == 125)
		ftol->y1 += 30 / ftol->zoom;
	else if (keys == 53)
		exit(0);
	redraw(ftol);
}

void	mouse_key(int keys, int x, int y, t_map *ftol)
{
	if (keys == 1)
	{
		if (ftol->flag_mouse == 1)
			ftol->flag_mouse = 0;
		else
			ftol->flag_mouse = 1;
	}
	if (keys == 4)
		zoomin(keys, x, y, ftol);
	else if (keys == 5)
		zoomout(keys, x, y, ftol);
}

void	julia_mouse(int x, int y, t_map *ftol)
{
	if (ftol->flag_mouse == 1)
	{
		ftol->ci = (double)(x - (double)SIZE / 2) / ((double)SIZE / 2);
		ftol->cr = (double)(y - (double)SIZE / 2) / ((double)SIZE / 2);
		redraw(ftol);
	}
}
