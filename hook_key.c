/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emende <emende@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 15:33:14 by emende            #+#    #+#             */
/*   Updated: 2022/04/03 23:52:03 by emende           ###   ########.fr       */
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
			free_intarr(v->arr, v->row_count);
		free(v);
	}
	exit (0);
}

static void	clear_image(t_vars *v)
{
	int	row;
	int	col;

	row = 0;
	while (row < W_HEIGHT)
	{
		col = 0;
		while (col < W_WIDTH)
		{
			ft_mlx_pixel_put(&v->data, col, row, 0);
			col++;
		}
		row++;
	}
}

static void	refresh(t_vars *v)
{
//	mlx_clear_window(v->mlx_ptr, v->win_ptr);
	clear_image(v);
	image_to_display(v);
}

void	image_to_display(t_vars *v)
{
	draw_iso(v, 0, 0);
	mlx_put_image_to_window(v->mlx_ptr, v->win_ptr, v->data.img, 0, 0);
	mlx_string_put(v->mlx_ptr, v->win_ptr, 20, 20, 0xFFFFFF, "Move: Arrows");
	mlx_string_put(v->mlx_ptr, v->win_ptr, 20, 40, 0xFFFFFF, "Flatten: -/+");
	mlx_string_put(v->mlx_ptr, v->win_ptr, 20, 60, 0xFFFFFF, "Zoom: A/S");
}

int	hook_key(int keycode, t_vars *v)
{
	ft_putnbr(keycode);
	ft_putchar('\n');
	if (keycode == 53)
		panic("", v);
	else if (keycode == 125)
		v->y_ofs -= 10;
	else if (keycode == 126)
		v->y_ofs += 10;
	else if (keycode == 124)
		v->x_ofs -= 10;
	else if (keycode == 123)
		v->x_ofs += 10;
	else if (keycode == 69 || keycode == 24)
		v->z_ofs += 1;
	else if (keycode == 78 || keycode == 27)
		v->z_ofs -= 1;
	else if (keycode == 0)
	{
		v->tile_h += 2;
		v->tile_w += 4;
	}
	else if (keycode == 1 && v->tile_h > 3)
	{
		v->tile_h -= 2;
		v->tile_w -= 4;
	}
	else
		return (0);
	refresh(v);
	return (0);
}
