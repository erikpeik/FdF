/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emende <emende@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 15:36:24 by emende            #+#    #+#             */
/*   Updated: 2022/04/02 23:19:42 by emende           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_vars	*set_vars(char *argv, int fd)
{
	t_vars	*v;

	v = (t_vars *) malloc(sizeof (t_vars));
	v->mlx_ptr = mlx_init();
	v->win_ptr = mlx_new_window(v->mlx_ptr, W_WIDTH, W_HEIGHT, "FdF");
	v->data.img = mlx_new_image(v->mlx_ptr, W_WIDTH * 2, W_HEIGHT * 2);
	v->data.addr = mlx_get_data_addr(v->data.img, &v->data.bpp, \
		&v->data.line_len, &v->data.endian);
	v->arr = read_values(fd, argv, v);
	v->x_ofs = W_WIDTH / 2;
	v->tile_w = 50;
/*	if (v->tile_w % 2 != 0 || v->tile_w < 4)
		v->tile_w++; */
	v->tile_h = v->tile_w / 2;
	v->y_ofs = W_HEIGHT / v->col_count + 100;
	v->z_ofs = (v->max_altitude - v->min_altitude);
	return (v);
}

static void	print_intarr(int **points, int row_count, int col_count)
{
	int	row;
	int	col;

	row = 0;
	while (row < row_count)
	{
		col = 0;
		while (col < col_count)
		{
			ft_putnbr(points[row][col]);
			if (col < col_count - 1)
				ft_putchar(' ');
			else
				ft_putchar('\n');
			col++;
		}
		row++;
	}
}

int	upd_col(int point1, int point2, t_vars *v)
{
	if (point1 != 0 || point2 != 0)
		v->color = 0xFF0000;
	else
		v->color = 0xFFFFFF;
	return (1);
}

void	draw_iso(t_vars *v, int x, int y)
{
	while (y < v->row_count)
	{
		x = 0;
		while (x <= v->col_count)
		{
			v->line.x0 = v->x_ofs + ((v->tile_w / 2) * (x - y));
			v->line.y0 = v->y_ofs + ((v->tile_h / 2) * (x + y)) - (v->arr[y][x] * v->z_ofs);
			v->line.x1 = v->line.x0 + (v->tile_w / 2);
			v->line.y1 = v->y_ofs + ((v->tile_h / 2) * ((x + 1) + y)) - (v->arr[y][x + 1] * v->z_ofs);
			if (x < v->col_count && upd_col(v->arr[y][x], v->arr[y][x + 1], v))
				draw_line(&v->data, v->line, v->color);
			if (y < v->row_count - 1 && upd_col(v->arr[y][x], v->arr[y + 1][x], v))
			{
				v->line.x1 -= v->tile_w;
				v->line.y1 = v->y_ofs + (v->tile_h / 2) * (x + (y + 1)) - (v->arr[y + 1][x] * v->z_ofs);
				draw_line(&v->data, v->line, v->color);
			}
			x++;
		}
		y++;
	}
}

void	image_to_display(t_vars *v)
{
	draw_iso(v, 0, 0);
	mlx_put_image_to_window(v->mlx_ptr, v->win_ptr, v->data.img, 0, 0);
	mlx_string_put(v->mlx_ptr, v->win_ptr, 20, 20, 0xFFFFFF, "Move: Arrows");
	mlx_string_put(v->mlx_ptr, v->win_ptr, 20, 40, 0xFFFFFF, "Flatten: -/+");
	mlx_string_put(v->mlx_ptr, v->win_ptr, 20, 60, 0xFFFFFF, "Zoom: A/S");
}

int	main(int argc, char **argv)
{
	t_vars	*v;
	int		fd;

	if (argc != 2)
		panic("usage: ./fdf source_file\n", NULL);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		panic("error: Open failed. No such file or directory.\n", NULL);
	v = set_vars(argv[1], fd);
	mlx_clear_window(v->mlx_ptr, v->win_ptr);
	image_to_display(v);
	mlx_hook(v->win_ptr, 2, 1L << 0, hook_key, v);
	mlx_loop(v->mlx_ptr);
	mlx_loop(v->mlx_ptr);
	return (0);
}
