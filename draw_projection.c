/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_projection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emende <emende@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 23:37:34 by emende            #+#    #+#             */
/*   Updated: 2022/04/10 00:30:20 by emende           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	set_line(t_vars *v, int x, int y)
{
	if (v->projection == 1)
	{
		v->line.x0 = v->x_ofs + ((int)((v->tile_w / 2) * (x - y)));
		v->line.y0 = v->y_ofs + ((int)(v->tile_h / 2) * (x + y)) \
			- ((int)((v->arr[y][x] * v->z_ofs) * v->z_ofs2));
		v->line.x1 = v->line.x0 + ((int)(v->tile_w / 2));
		v->line.y1 = v->y_ofs + ((int)(v->tile_h / 2) * ((x + 1) + y)) \
			- ((int)((v->arr[y][x + 1] * v->z_ofs) * v->z_ofs2));
	}
	if (v->projection == 2)
	{
		v->line.x0 = (v->x_ofs - (W_WIDTH / 5)) + ((int)((v->tile_w / 2) * x));
		v->line.y0 = v->y_ofs + ((int)(v->tile_h * y));
		v->line.x1 = v->line.x0 + ((int)(v->tile_w / 2));
		v->line.y1 = v->y_ofs + ((int)(v->tile_h * y));
	}
	if (v->projection == 3)
	{
		v->line.x0 = (v->x_ofs - (W_WIDTH / 5)) + ((int)((v->tile_w / 2) * x));
		v->line.y0 = (v->y_ofs + 300) \
			- ((int)((v->arr[y][x] * v->z_ofs) * v->z_ofs2));
		v->line.x1 = v->line.x0 + ((int)(v->tile_w / 2));
		v->line.y1 = (v->y_ofs + 300) \
			- ((int)((v->arr[y][x + 1] * v->z_ofs) * v->z_ofs2));
	}
}

static void	draw_iso(t_vars *v, int x, int y)
{
	while (y < v->row_count)
	{
		x = 0;
		while (x <= v->col_count)
		{
			set_line(v, x, y);
			upd_col(v->arr[y][x], v->arr[y][x], v);
			ft_mlx_pixel_put(v, v->line.x0, v->line.y0);
			if (x < v->col_count && upd_col(v->arr[y][x], v->arr[y][x + 1], v))
				draw_line(v);
			if (y < v->row_count - 1
				&& upd_col(v->arr[y][x], v->arr[y + 1][x], v))
			{
				v->line.x1 -= (int) v->tile_w;
				v->line.y1 = v->y_ofs + ((int)(v->tile_h / 2) * (x + (y + 1))) \
					- ((int)((v->arr[y + 1][x] * v->z_ofs) * v->z_ofs2));
				draw_line(v);
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
			set_line(v, x, y);
			upd_col(v->arr[y][x], v->arr[y][x], v);
			ft_mlx_pixel_put(v, v->line.x0, v->line.y0);
			if (x < v->col_count && upd_col(v->arr[y][x], v->arr[y][x + 1], v))
				draw_line(v);
			if (y < v->row_count - 1 \
				&& upd_col(v->arr[y][x], v->arr[y + 1][x], v))
			{
				v->line.x1 -= (int) v->tile_w / 2;
				v->line.y1 = v->y_ofs + ((int)(v->tile_h * (y + 1)));
				draw_line(v);
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
			set_line(v, x, y);
			upd_col(v->arr[y][x], v->arr[y][x], v);
			ft_mlx_pixel_put(v, v->line.x0, v->line.y0);
			if (x < v->col_count && upd_col(v->arr[y][x], v->arr[y][x + 1], v))
				draw_line(v);
			if (y < v->row_count - 1 && v->arr[y][x] != 0)
			{
				v->line.y1 = (v->y_ofs + 300) \
					- ((int)((v->arr[y + 1][x] * v->z_ofs) * v->z_ofs2));
				v->line.x1 = v->line.x0;
				draw_line(v);
			}
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
