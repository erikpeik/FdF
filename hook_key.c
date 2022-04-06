/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emende <emende@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 15:33:14 by emende            #+#    #+#             */
/*   Updated: 2022/04/06 16:58:47 by emende           ###   ########.fr       */
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
	{
		v->tile_h += 2;
		v->tile_w += 4;
	}
	if ((keycode == 1 || keycode == 115) && v->tile_h > 3)
	{
		v->tile_h -= 2;
		v->tile_w -= 4;
	}
}

static void	change_colortheme(int keycode, t_vars *v)
{
	if (keycode == 8 || keycode == 99)
	{
		if (v->color_theme == 4)
			v->color_theme = 0;
		else
			v->color_theme++;
	}
	if (keycode == 37 || keycode == 108)
	{
		if (v->light_switch == 0)
			v->light_switch = 1;
		else
			v->light_switch = 0;
	}
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

int	hook_key(int keycode, t_vars *v)
{
	int	key;

	key = keycode;
	ft_putnbr_endl(key);
	if (key == 53 || key == 0xFF1B)
		panic("", v);
	else if ((key >= 123 && key <= 126) || (key >= 0xff51 && key <= 0xff54))
		move_arrows(key, v);
	else if (key == 69 || key == 24 || key == 0xfe51 || key == 0xffab)
		v->z_ofs += 1;
	else if (key == 78 || key == 27 || key == 43 || key == 0xffad)
		v->z_ofs -= 1;
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
