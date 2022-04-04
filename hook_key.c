/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emende <emende@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 15:33:14 by emende            #+#    #+#             */
/*   Updated: 2022/04/04 12:14:48 by emende           ###   ########.fr       */
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

static void	move_arrows(int keycode, t_vars *v)
{
	if (keycode == 125)
		v->y_ofs -= 10;
	if (keycode == 126)
		v->y_ofs += 10;
	if (keycode == 124)
		v->x_ofs -= 10;
	if (keycode == 123)
		v->x_ofs += 10;
}

static void	flatten_z(int keycode, t_vars *v)
{
	if (keycode == 0)
	{
		v->tile_h += 2;
		v->tile_w += 4;
	}
	if (keycode == 1 && v->tile_h > 3)
	{
		v->tile_h -= 2;
		v->tile_w -= 4;
	}
}

int	hook_key(int keycode, t_vars *v)
{
	ft_putnbr(keycode);
	ft_putchar('\n');
	if (keycode == 53)
		panic("", v);
	else if (keycode >= 123 && keycode <= 126)
		move_arrows(keycode, v);
	else if (keycode == 69 || keycode == 24)
		v->z_ofs += 1;
	else if (keycode == 78 || keycode == 27)
		v->z_ofs -= 1;
	else if (keycode == 0 || keycode == 1)
		flatten_z(keycode, v);
	else if (keycode == 18)
		v->projection = 1;
	else if (keycode == 19)
		v->projection = 2;
	else if (keycode == 20)
		v->projection = 3;
	else
		return (0);
	refresh(v);
	return (0);
}
