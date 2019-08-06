/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burningship.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arunte <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 17:13:01 by arunte            #+#    #+#             */
/*   Updated: 2019/05/25 18:17:48 by arunte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		burningship_init(t_map *ftol)
{
	ftol->max_i = 200;
	ftol->zoom = SIZE / 4;
	ftol->x1 = -2.2;
	ftol->y1 = -2.5;
	ftol->color = 265;
}

void		*draw_ship(void *ftol)
{
	while (((t_map *)ftol)->y < ((t_map *)ftol)->y_max)
	{
		((t_map *)ftol)->x = 0;
		while (((t_map *)ftol)->x < SIZE)
		{
			burningship_calc((t_map *)ftol);
			((t_map *)ftol)->x++;
		}
		((t_map *)ftol)->y++;
	}
	return (ftol);
}

void		burningship_calc(t_map *ftol)
{
	ftol->cr = ftol->x / ftol->zoom + ftol->x1;
	ftol->ci = ftol->y / ftol->zoom + ftol->y1;
	ftol->zr = 0;
	ftol->zi = 0;
	ftol->min_i = 0;
	while (ftol->zr * ftol->zr + ftol->zi * ftol->zi < 4
			&& ftol->min_i < ftol->max_i)
	{
		ftol->tmp = ftol->zr * ftol->zr - ftol->zi * ftol->zi + ftol->cr;
		ftol->zi = fabs(2 * ftol->zr * ftol->zi) + ftol->ci;
		ftol->zr = ftol->tmp;
		ftol->min_i++;
	}
	if (ftol->min_i == ftol->max_i)
	{
		put_pix_img(ftol, ftol->x, ftol->y, 0xFFFFFF);
	}
	else
	{
		put_pix_img(ftol, ftol->x, ftol->y, (ftol->color * ftol->min_i));
	}
}

void		burningship_pthread(t_map *ftol)
{
	t_map		tab[THREAD_NUMBER];
	pthread_t	t[THREAD_NUMBER];
	int			i;

	i = 0;
	while (i < THREAD_NUMBER)
	{
		ft_memcpy((void *)(&tab[i]), (void *)ftol, sizeof(t_map));
		tab[i].y = THREAD_WIDTH * i;
		tab[i].y_max = THREAD_WIDTH * (i + 1);
		pthread_create(&t[i], NULL, (void *)draw_ship, &tab[i]);
		i++;
	}
	while (i--)
	{
		pthread_join(t[i], NULL);
	}
	mlx_put_image_to_window(ftol->window.mlx_ptr, ftol->window.win_ptr,
							ftol->img.img_ptr, 0, 0);
}
