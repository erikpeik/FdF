/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emende <emende@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 15:36:24 by emende            #+#    #+#             */
/*   Updated: 2022/04/04 16:53:11 by emende           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_vars	*set_vars(char *argv, int fd)
{
	t_vars	*v;

	v = (t_vars *) malloc(sizeof (t_vars));
	if (!v)
		panic("error: malloc fail", NULL);
	v->mlx_ptr = mlx_init();
	if (!v->mlx_ptr)
		panic("error: failed creating mlx_ptr\n", v);
	v->win_ptr = mlx_new_window(v->mlx_ptr, W_WIDTH, W_HEIGHT, "FdF");
	if (!v->win_ptr)
		panic("error: failed creating win_ptr\n", v);
	v->data.img = mlx_new_image(v->mlx_ptr, W_WIDTH, W_HEIGHT);
	v->data.addr = mlx_get_data_addr(v->data.img, &v->data.bpp, \
		&v->data.line_len, &v->data.endian);
	v->arr = read_values(fd, argv, v);
	v->tile_w = 100;
	v->tile_h = v->tile_w / 2;
	v->x_ofs = W_WIDTH / 2;
	v->y_ofs = 100;
	v->z_ofs = 5;
	v->projection = 1;
	initilize_colors(v);
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
	refresh(v);
	mlx_hook(v->win_ptr, 2, 1L << 0, hook_key, v);
	mlx_loop(v->mlx_ptr);
	return (0);
}
