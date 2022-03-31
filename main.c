/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emende <emende@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 15:36:24 by emende            #+#    #+#             */
/*   Updated: 2022/03/31 13:01:07 by emende           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	panic(char	*msg, t_vars *v)
{
	ft_putstr_fd(msg, 2);
	exit (0);
}

int	hook_key(int keycode, t_vars *v)
{
	ft_putnbr(keycode);
	ft_putchar('\n');
	if (keycode == 53)
	{
		if (v->mlx_ptr && v->data.img)
			mlx_destroy_image(v->mlx_ptr, v->data.img);
		if (v->mlx_ptr && v->win_ptr)
			mlx_destroy_window(v->mlx_ptr, v->win_ptr);
		exit (-1);
	}
	return (0);
}

t_vars	*set_vars()
{}

int	main(void)
{
	t_vars	*v;
	int		temp;

	v = set_vars();
	v->mlx_ptr = mlx_init();
	v->win_ptr = mlx_new_window(v->mlx_ptr, W_WIDTH, W_HEIGHT, "FdF");
	v->data.img = mlx_new_image(v->mlx_ptr, W_WIDTH, W_HEIGHT);
	v->data.addr = mlx_get_data_addr(v->data.img, &v->data.bpp, \
			&v->data.line_len, &v->data.endian);
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
//	draw_line(&img, line, 0xFFFFFF);
	return (0);
}
