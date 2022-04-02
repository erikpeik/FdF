/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emende <emende@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 15:36:24 by emende            #+#    #+#             */
/*   Updated: 2022/04/02 14:33:42 by emende           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_vars	*set_vars(void)
{
	t_vars	*v;

	v = (t_vars *) malloc(sizeof (t_vars));
	v->mlx_ptr = mlx_init();
	v->win_ptr = mlx_new_window(v->mlx_ptr, W_WIDTH, W_HEIGHT, "FdF");
	v->data.img = mlx_new_image(v->mlx_ptr, W_WIDTH * 2, W_HEIGHT * 2);
	v->data.addr = mlx_get_data_addr(v->data.img, &v->data.bpp, \
			&v->data.line_len, &v->data.endian);
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

void draw_iso(t_vars *v)
{

}

int	main(int argc, char **argv)
{
	t_vars	*v;
	int		**points;
	int		fd;
	int		x;
	int		y;

	if (argc != 2)
		panic("usage: ./fdf source_file\n", NULL);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		panic("error: Open failed. No such file or directory.\n", NULL);
	v = set_vars();
	points = read_values(fd, argv[1], v);
/*	ft_putnbr(v->row_count);
	ft_putchar('\n');
	ft_putnbr(v->nums_line);
	ft_putchar('\n'); */
	print_intarr(points, v->row_count, v->col_count);
	y = 0;
	while (y < v->row_count)
	{
		x = 0;
		while (x < v->col_count)
		{
			v->line.begin_x = W_WIDTH / 2 + ((TILE_W / 2) * (x - y));
			v->line.begin_y = W_HEIGHT / 4 + ((TILE_H / 2) * (x + y)) - (points[y][x] * 5);
			v->line.end_x = v->line.begin_x + (TILE_W / 2);
			v->line.end_y = W_HEIGHT / 4 + ((TILE_H / 2) * ((x + 1) + y)) - (points[y][x + 1] * 5);
			draw_line(&v->data, v->line, 0xFFFFFF);
			x++;
		}
		y++;
	}


	free_intarr(points, 9);
/*	system("leaks fdf"); */
/*	draw_block(v, 0, 0, 0);
	draw_block(v, 1, 0, 0);
	draw_block(v, 0, 1, 0);
	draw_block(v, 0, 0, 1); */
	mlx_put_image_to_window(v->mlx_ptr, v->win_ptr, v->data.img, 0, 0);
	mlx_key_hook(v->win_ptr, hook_key, v);
	mlx_loop(v->mlx_ptr);
	return (0);
}
