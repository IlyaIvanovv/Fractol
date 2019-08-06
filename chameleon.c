/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chameleon.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arunte <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 18:06:03 by arunte            #+#    #+#             */
/*   Updated: 2019/05/25 18:18:45 by arunte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	init_chameleon(t_map *ftol)
{
	ftol->zoom = SIZE / 4;
	ftol->max_i = 140;
	ftol->x1 = -2;
	ftol->y1 = -2;
	ftol->color = 0xbc182b;
	ftol->cr = 0.29;
	ftol->ci = 0.02;
}

void	calc_chameleon(t_map *ftol)
{
	ftol->min_i = 0;
	ftol->zr = ftol->x / ftol->zoom + ftol->x1;
	ftol->zi = ftol->y / ftol->zoom + ftol->y1;
	while (ftol->zr * ftol->zr + ftol->zi * ftol->zi < 4 &&
			ftol->min_i < ftol->max_i)
	{
		ftol->tmp = ftol->zr;
		ftol->zr = ftol->zr * ftol->zr - ftol->zi * ftol->zi + ftol->cr;
		ftol->zi = -2 * ftol->zi * ftol->tmp + ftol->ci;
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

void	*draw_chameleon(void *ftol)
{
	while (((t_map *)ftol)->y < ((t_map *)ftol)->y_max)
	{
		((t_map *)ftol)->x = 0;
		while (((t_map *)ftol)->x < SIZE)
		{
			calc_chameleon((t_map *)ftol);
			((t_map *)ftol)->x++;
		}
		((t_map *)ftol)->y++;
	}
	return (ftol);
}

void	chameleon_pthread(t_map *ftol)
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
		pthread_create(&t[i], NULL, (void *)draw_chameleon, &tab[i]);
		i++;
	}
	while (i--)
	{
		pthread_join(t[i], NULL);
	}
	mlx_put_image_to_window(ftol->window.mlx_ptr, ftol->window.win_ptr,
							ftol->img.img_ptr, 0, 0);
}
