/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tile_and_block.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emende <emende@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 17:42:51 by emende            #+#    #+#             */
/*   Updated: 2022/04/02 22:46:21 by emende           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_tile(t_vars *v, int x, int y, int color)
{
	v->line.x0 = W_WIDTH / 2 + ((v->tile_w / 2) * (x - y));
	v->line.y0 = v->tile_h + ((v->tile_h / 2) * (x + y));
	v->line.x1 = v->line.x0 - (v->tile_w / 2);
	v->line.y1 = v->line.y0 + (v->tile_h / 2);
	draw_line(&v->data, v->line, color);
	v->line.x1 += v->tile_w;
	draw_line(&v->data, v->line, color);
	v->line.y0 += v->tile_h;
	draw_line(&v->data, v->line, color);
	v->line.x1 -= v->tile_w;
	draw_line(&v->data, v->line, color);
}

static void	draw_left_and_right(t_vars *v, int x, int y)
{
	int	color;

	color = 0xFFFFFF;
	v->line.x0 = W_WIDTH / 2 + ((v->tile_w / 2) * (x - y));
	v->line.x1 = v->line.x0;
	v->line.y1 = v->line.y0 + v->tile_h;
	draw_line(&v->data, v->line, color);
	v->line.x0 += v->tile_w / 2;
	v->line.y0 += v->tile_h / 2;
	draw_line(&v->data, v->line, color);
	v->line.x1 = v->line.x0;
	v->line.y1 = v->line.y0 - v->tile_w / 2;
	draw_line(&v->data, v->line, color);
	v->line.x0 -= v->tile_w;
	v->line.x1 -= v->tile_w;
	draw_line(&v->data, v->line, color);
	v->line.x1 += v->tile_w / 2;
	v->line.y1 = v->line.y0 + v->tile_h / 2;
	draw_line(&v->data, v->line, color);
}

void	draw_block(t_vars *v, int x, int y, int z)
{
	int	color;

	color = 0xFFFFFF;
	v->line.x0 = W_WIDTH / 2 + ((v->tile_w / 2) * (x - y));
	v->line.y0 = (v->tile_h * 3 / 2) + (v->tile_h / 2 * (x + y)) - (z * v->tile_h);
	v->line.x1 = v->line.x0 - (v->tile_w / 2);
	v->line.y1 = v->line.y0 + (v->tile_h / 2);
	draw_line(&v->data, v->line, color);
	v->line.x1 += v->tile_w;
	draw_line(&v->data, v->line, color);
	v->line.y0 += v->tile_h;
	draw_line(&v->data, v->line, color);
	v->line.x1 -= v->tile_w;
	draw_line(&v->data, v->line, color);
	draw_left_and_right(v, x, y);
}
