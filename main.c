/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emende <emende@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 15:36:24 by emende            #+#    #+#             */
/*   Updated: 2022/04/09 23:25:42 by emende           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	panic(char	*msg, t_vars *v)
{
	ft_putstr_fd(msg, 2);
	if (v)
	{
		if (v->mlx_ptr && v->data.img)
			mlx_destroy_image(v->mlx_ptr, v->data.img);
		if (v->mlx_ptr && v->win_ptr)
			mlx_destroy_window(v->mlx_ptr, v->win_ptr);
		if (v->arr && v->row_count > 0)
			free_intarr(&v->arr, v->row_count);
	}
	exit (0);
}

static t_vars	set_vars(char *argv, int fd)
{
	t_vars	v;

	v.mlx_ptr = mlx_init();
	if (!v.mlx_ptr)
		panic("error: failed creating mlx_ptr\n", &v);
	v.win_ptr = mlx_new_window(v.mlx_ptr, W_WIDTH, W_HEIGHT, "FdF");
	if (!v.win_ptr)
		panic("error: failed creating win_ptr\n", &v);
	v.data.img = mlx_new_image(v.mlx_ptr, W_WIDTH, W_HEIGHT);
	v.data.addr = mlx_get_data_addr(v.data.img, &v.data.bpp, \
		&v.data.line_len, &v.data.endian);
	v.row_count = 0;
	v.col_count = 0;
	read_values(fd, argv, &v);
	v.tile_w = 80;
	v.tile_h = v.tile_w / 2;
	v.x_ofs = W_WIDTH / 2;
	v.y_ofs = W_HEIGHT / 4;
	v.z_ofs = v.tile_h;
	v.z_ofs2 = 1;
	v.projection = 1;
	return (v);
}

int	main(int argc, char **argv)
{
	t_vars	v;
	int		fd;

	if (argc != 2)
		panic("usage: ./fdf source_file\n", NULL);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		panic("error: Open failed. No such file or directory.\n", NULL);
	v = set_vars(argv[1], fd);
	initilize_colors(&v);
	mlx_clear_window(v.mlx_ptr, v.win_ptr);
	refresh(&v);
	mlx_hook(v.win_ptr, 2, 1L << 0, hook_key, &v);
	mlx_loop(v.mlx_ptr);
	return (0);
}
