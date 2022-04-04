/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emende <emende@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 15:36:24 by emende            #+#    #+#             */
/*   Updated: 2022/04/04 11:50:06 by emende           ###   ########.fr       */
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
	v->tile_w = W_WIDTH / v->col_count;
	v->tile_h = v->tile_w / 2;
	v->x_ofs = W_WIDTH / 2;
	v->y_ofs = 100;
	v->z_ofs = 5;
	v->projection = 1;
	return (v);
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
	return (0);
}
