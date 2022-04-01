/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emende <emende@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 15:36:24 by emende            #+#    #+#             */
/*   Updated: 2022/04/01 17:41:03 by emende           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_vars	*set_vars(void)
{
	t_vars	*v;

	v = (t_vars *) malloc(sizeof (t_vars));
	v->mlx_ptr = mlx_init();
	v->win_ptr = mlx_new_window(v->mlx_ptr, W_WIDTH, W_HEIGHT, "FdF");
	v->data.img = mlx_new_image(v->mlx_ptr, W_WIDTH, W_HEIGHT);
	v->data.addr = mlx_get_data_addr(v->data.img, &v->data.bpp, \
			&v->data.line_len, &v->data.endian);
	return (v);
}

int	main(void)
{
	t_vars	*v;
	int		temp;

	v = set_vars();
/*	for (int x = 0; x < 15; x++)
		for (int y = 0; y < 15; y++)
			drawTile(v, x, y, 0xFFFFFF); */
	draw_block(v, 0, 0, 1);
	draw_block(v, 0, 0, 0);
	draw_block(v, 0, 1, 0);
	draw_block(v, 1, 0, 0);
	mlx_put_image_to_window(v->mlx_ptr, v->win_ptr, v->data.img, 0, 0);
	mlx_key_hook(v->win_ptr, hook_key, v);
	mlx_loop(v->mlx_ptr);
	return (0);
}
