/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arunte <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 17:56:28 by arunte            #+#    #+#             */
/*   Updated: 2019/05/25 18:02:27 by arunte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	draw_ftol(t_map *ftol)
{
	if (ftol->init_ftol == 0)
		mbrot_pthread(ftol);
	else if (ftol->init_ftol == 1)
		julia_pthread(ftol);
	else if (ftol->init_ftol == 2)
		burningship_pthread(ftol);
	else if (ftol->init_ftol == 3)
		chameleon_pthread(ftol);
	else
		ft_putstr("draw error");
}

void	init_ftol(t_map *ftol)
{
	if (ftol->init_ftol == 0)
		init_mbrot(ftol);\
	else if (ftol->init_ftol == 1)
		init_julia(ftol);
	else if (ftol->init_ftol == 2)
		burningship_init(ftol);
	else if (ftol->init_ftol == 3)
		init_chameleon(ftol);
	draw_ftol(ftol);
}

int		preset_ftol(char *argv, t_map *ftol)
{
	if (ft_strequ(argv, "Mandelbrot") == 1)
		ftol->init_ftol = 0;
	else if (ft_strequ(argv, "Julia") == 1)
		ftol->init_ftol = 1;
	else if (ft_strequ(argv, "Ship") == 1)
		ftol->init_ftol = 2;
	else if (ft_strequ(argv, "Chameleon") == 1)
		ftol->init_ftol = 3;
	else
	{
		return (usage());
	}
	return (1);
}

void	mlx(t_map *ftol)
{
	ftol->window.mlx_ptr = mlx_init();
	ftol->window.win_ptr = mlx_new_window(ftol->window.mlx_ptr,
			SIZE, SIZE, "Fractal");
	ftol->img.img_ptr = mlx_new_image(ftol->window.mlx_ptr, SIZE, SIZE);
	ftol->img.data = (unsigned int *)mlx_get_data_addr(ftol->img.img_ptr,
			&ftol->img.bits_per_pixel,
			&ftol->img.size_line,
			&ftol->img.end);
}

int		main(int argc, char **argv)
{
	t_map *ftol;

	if (!(ftol = (t_map *)malloc(sizeof(t_map))))
		return (-1);
	if (argc != 2)
		usage();
	if (argc == 2)
	{
		mlx(ftol);
		if (preset_ftol(argv[1], ftol) == 0)
			return (0);
		init_ftol(ftol);
		draw_img(ftol->window.mlx_ptr, ftol->window.win_ptr, ftol->img);
		mlx_key_hook(ftol->window.win_ptr, (void *)key_pressed, ftol);
		mlx_hook(ftol->window.win_ptr, 6, 0, (void *)julia_mouse, ftol);
		mlx_hook(ftol->window.win_ptr, 17, 0, (void *)exit_x, NULL);
		mlx_hook(ftol->window.win_ptr, 4, 0, (void *)mouse_key, ftol);
		mlx_loop(ftol->window.mlx_ptr);
	}
	return (0);
}
