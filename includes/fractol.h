/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FdF.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arunte <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 13:10:30 by arunte            #+#    #+#             */
/*   Updated: 2019/06/06 15:03:39 by arunte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "/usr/local/include/mlx.h"
# include <stdlib.h>
# include "math.h"
# include "libft.h"
# include "pthread.h"

# define SIZE 900
# define THREAD_NUMBER 16
# define THREAD_WIDTH (SIZE / THREAD_NUMBER)

typedef struct		s_window
{
	void			*mlx_ptr;
	void			*win_ptr;
}					t_window;

typedef struct		s_img
{
	void			*img_ptr;
	unsigned int	*data;
	int				size_line;
	int				end;
	int				bits_per_pixel;
}					t_img;

typedef struct		s_map
{
	t_window		window;
	t_img			img;
	int				x;
	int				y;
	int				y_max;
	double			x1;
	double			y1;
	double			cr;
	double			ci;
	double			tmp;
	double			zr;
	double			zi;
	int				init_ftol;
	int				color;
	double			zoom;
	int				min_i;
	int				max_i;
	int				flag_mouse;
}					t_map;

void				put_pix_img(t_map *ftol, int x, int y, unsigned int color);

int					draw_img(void *mlx, void *win, t_img img);

void				burningship_calc(t_map *ftol);

void				burningship_init(t_map *ftol);

void				init_chameleon(t_map *ftol);

void				*draw_chameleon(void *ftol);

void				chameleon_pthread(t_map *ftol);

void				mbrot_pthread(t_map *ftol);

void				burningship_pthread(t_map *ftol);

void				*draw_ship(void *ftol);

void				calc_mbrot(t_map *ftol);

void				init_mbrot(t_map *ftol);

void				*draw_mbrot(void *ftol);

void				draw_ftol(t_map *ftol);

void				calc_julia(t_map *ftol);

void				init_julia(t_map *ftol);

int					usage(void);

void				key_pressed(int keys, t_map *ftol);

int					exit_x(void);

void				redraw(t_map *ftol);

void				*draw_julia(void *ftol);

void				zoomin(int keys, int x, int y, t_map *ftol);

void				zoomout(int keys, int x, int y, t_map *ftol);

void				julia_mouse(int x, int y, t_map *ftol);

void				mouse_key(int button, int x, int y, t_map *ftol);

void				julia_pthread(t_map *ftol);

#endif
