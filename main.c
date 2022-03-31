/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emende <emende@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 15:36:24 by emende            #+#    #+#             */
/*   Updated: 2022/03/31 15:33:30 by emende           ###   ########.fr       */
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
	v->line.begin_x = W_WIDTH / 2;
	v->line.begin_y = W_HEIGHT / 2;
	temp = 0;
	v->line.end_y = 0;
	while (temp <= W_WIDTH)
	{
		v->line.end_x = temp;
		draw_line(&v->data, v->line, 0xFFFFFF);
		temp += 50;
	}
	temp = 50;
	v->line.end_x = W_WIDTH;
	while (temp <= W_HEIGHT)
	{
		v->line.end_y = temp;
		draw_line(&v->data, v->line, 0xFFFFFF);
		temp += 50;
	}
	temp = W_WIDTH - 50;
	v->line.end_y = W_HEIGHT;
	while (temp >= 0)
	{
		v->line.end_x = temp;
		draw_line(&v->data, v->line, 0xFFFFFF);
		temp -= 50;
	}
	temp = W_HEIGHT - 50;
	v->line.end_x = 0;
	while (temp >= 0)
	{
		v->line.end_y = temp;
		draw_line(&v->data, v->line, 0xFFFFFF);
		temp -= 50;
	}
	mlx_put_image_to_window(v->mlx_ptr, v->win_ptr, v->data.img, 0, 0);
	mlx_key_hook(v->win_ptr, hook_key, v);
	mlx_loop(v->mlx_ptr);
	return (0);
}
