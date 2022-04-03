/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_projection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emende <emende@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 23:37:34 by emende            #+#    #+#             */
/*   Updated: 2022/04/03 23:58:00 by emende           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	upd_col(int point1, int point2, t_vars *v)
{
	if (point1 != 0 || point2 != 0)
		v->color = 0xFF0000;
	else
		v->color = 0xFFFFFF;
	return (1);
}

void	draw_iso(t_vars *v, int x, int y)
{
	while (y < v->row_count)
	{
		x = 0;
		while (x <= v->col_count)
		{
			v->line.x0 = v->x_ofs + ((v->tile_w / 2) * (x - y));
			v->line.y0 = v->y_ofs + (v->tile_h / 2) * (x + y)
				- (v->arr[y][x] * v->z_ofs);
			v->line.x1 = v->line.x0 + (v->tile_w / 2);
			v->line.y1 = v->y_ofs + (v->tile_h / 2) * ((x + 1) + y)
				- (v->arr[y][x + 1] * v->z_ofs);
			if (x < v->col_count && upd_col(v->arr[y][x], v->arr[y][x + 1], v))
				draw_line(&v->data, v->line, v->color);
			if (y < v->row_count - 1
				&& upd_col(v->arr[y][x], v->arr[y + 1][x], v))
			{
				v->line.x1 -= v->tile_w;
				v->line.y1 = v->y_ofs + (v->tile_h / 2) * (x + (y + 1))
					- (v->arr[y + 1][x] * v->z_ofs);
				draw_line(&v->data, v->line, v->color);
			}
			x++;
		}
		y++;
	}
}