/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emende <emende@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 15:33:14 by emende            #+#    #+#             */
/*   Updated: 2022/04/09 23:41:57 by emende           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	move_arrows(int keycode, t_vars *v)
{
	if (keycode == 125 || keycode == 0xff54)
		v->y_ofs -= 10;
	if (keycode == 126 || keycode == 0xff52)
		v->y_ofs += 10;
	if (keycode == 124 || keycode == 0xff53)
		v->x_ofs -= 10;
	if (keycode == 123 || keycode == 0xff51)
		v->x_ofs += 10;
}

static void	tile_size(int keycode, t_vars *v)
{
	if (keycode == 0 || keycode == 97)
		v->tile_w += 4;
	if ((keycode == 1 || keycode == 115) && v->tile_h > 3)
		v->tile_w -= 4;
	v->tile_h = v->tile_w / 2;
	v->z_ofs = v->tile_h;
}

static void	change_projection(int keycode, t_vars *v)
{
	if (keycode == 18 || keycode == 49)
		v->projection = 1;
	else if (keycode == 19 || keycode == 50)
		v->projection = 2;
	else if (keycode == 20 || keycode == 51)
		v->projection = 3;
}

static void	change_altitude(int keycode, t_vars *v)
{
	int		key;
	double	range;

	range = v->z_ofs / 2;
	key = keycode;
	if (key == 69 || key == 24 || key == 0xfe51 || key == 0xffab)
	{
		if (v->z_ofs2 * v->z_ofs > range || v->z_ofs2 * v->z_ofs < -range)
			v->z_ofs2 += 0.1;
		else if (v->z_ofs2 * v->z_ofs > range / 2 \
			|| v->z_ofs2 * v->z_ofs < -range / 2)
			v->z_ofs2 += 0.05;
		else
			v->z_ofs2 += 0.01;
	}
	else if (key == 78 || key == 27 || key == 43 || key == 0xffad)
	{
		if (v->z_ofs2 * v->z_ofs > range || v->z_ofs2 * v->z_ofs < -range)
			v->z_ofs2 -= 0.1;
		else if (v->z_ofs2 * v->z_ofs > range / 2 \
			|| v->z_ofs2 * v->z_ofs < -range / 2)
			v->z_ofs2 -= 0.05;
		else
			v->z_ofs2 -= 0.01;
	}
}

int	hook_key(int keycode, t_vars *v)
{
	int	key;

	key = keycode;
	ft_putnbr_endl(key);
	if (key == 53 || key == 0xff1b)
		panic("", v);
	else if ((key >= 123 && key <= 126) || (key >= 0xff51 && key <= 0xff54))
		move_arrows(key, v);
	else if (key == 69 || key == 24 || key == 0xfe51 || key == 0xffab \
		|| key == 78 || key == 27 || key == 43 || key == 0xffad)
		change_altitude(key, v);
	else if (key == 0 || key == 1 || key == 97 || key == 115)
		tile_size(key, v);
	else if ((key >= 18 && key <= 20) || (key >= 49 && key <= 51))
		change_projection(key, v);
	else if (key == 8 || key == 37 || key == 99 || key == 108)
		change_colortheme(key, v);
	else
	{
		ft_putstr("Key that you pressed is not mapped.\n");
		return (0);
	}
	refresh(v);
	return (0);
}
