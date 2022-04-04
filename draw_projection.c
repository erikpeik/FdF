/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_projection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emende <emende@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 23:37:34 by emende            #+#    #+#             */
/*   Updated: 2022/04/04 12:16:52 by emende           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	upd_col(int point1, int point2, t_vars *v)
{
	if (point1 * v->z_ofs != 0 || point2 * v->z_ofs != 0)
		v->color = 0xFF0000;
	else
		v->color = 0xFFFFFF;
	return (1);
}

static void	draw_iso(t_vars *v, int x, int y)
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

static void	topdown(t_vars *v, int x, int y)
{
	while (y < v->row_count)
	{
		x = 0;
		while (x <= v->col_count)
		{
			v->line.x0 = (v->x_ofs - 200) + ((v->tile_w / 2) * x);
			v->line.y0 = v->y_ofs + (v->tile_h * y);
			v->line.x1 = v->line.x0 + (v->tile_w / 2);
			v->line.y1 = v->y_ofs + (v->tile_h * y);
			if (x < v->col_count && upd_col(v->arr[y][x], v->arr[y][x + 1], v))
				draw_line(&v->data, v->line, v->color);
			if (y < v->row_count - 1
				&& upd_col(v->arr[y][x], v->arr[y + 1][x], v))
			{
				v->line.x1 -= v->tile_w / 2;
				v->line.y1 = v->y_ofs + (v->tile_h * (y + 1));
				draw_line(&v->data, v->line, v->color);
			}
			x++;
		}
		y++;
	}
}

static void	sideview_x(t_vars *v, int x, int y)
{
	while (y < v->row_count)
	{
		x = 0;
		while (x <= v->col_count)
		{
			v->line.x0 = (v->x_ofs - 200) + ((v->tile_w / 2) * x);
			v->line.y0 = (v->y_ofs + 300) - (v->arr[y][x] * v->z_ofs);
			v->line.x1 = v->line.x0 + (v->tile_w / 2);
			v->line.y1 = (v->y_ofs + 300) - (v->arr[y][x + 1] * v->z_ofs);
			if (x < v->col_count && upd_col(v->arr[y][x], v->arr[y][x + 1], v))
				draw_line(&v->data, v->line, v->color);
			x++;
		}
		y++;
	}
}

void	projection(t_vars *v)
{
	if (v->projection == 1)
		draw_iso(v, 0, 0);
	if (v->projection == 2)
		topdown(v, 0, 0);
	if (v->projection == 3)
		sideview_x(v, 0, 0);
}
