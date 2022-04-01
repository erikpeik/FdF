/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tile_and_block.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emende <emende@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 17:42:51 by emende            #+#    #+#             */
/*   Updated: 2022/04/01 19:52:04 by emende           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_tile(t_vars *v, int x, int y, int color)
{
	v->line.begin_x = W_WIDTH / 2 + ((TILE_W / 2) * (x - y));
	v->line.begin_y = TILE_H + ((TILE_H / 2) * (x + y));
	v->line.end_x = v->line.begin_x - (TILE_W / 2);
	v->line.end_y = v->line.begin_y + (TILE_H / 2);
	draw_line(&v->data, v->line, color);
	v->line.end_x += TILE_W;
	draw_line(&v->data, v->line, color);
	v->line.begin_y += TILE_H;
	draw_line(&v->data, v->line, color);
	v->line.end_x -= TILE_W;
	draw_line(&v->data, v->line, color);
}

static void	draw_left_and_right(t_vars *v, int x, int y)
{
	int	color;

	color = 0xFFFFFF;
	v->line.begin_x = W_WIDTH / 2 + ((TILE_W / 2) * (x - y));
	v->line.end_x = v->line.begin_x;
	v->line.end_y = v->line.begin_y + TILE_H;
	draw_line(&v->data, v->line, color);
	v->line.begin_x += TILE_W / 2;
	v->line.begin_y += TILE_H / 2;
	draw_line(&v->data, v->line, color);
	v->line.end_x = v->line.begin_x;
	v->line.end_y = v->line.begin_y - TILE_W / 2;
	draw_line(&v->data, v->line, color);
	v->line.begin_x -= TILE_W;
	v->line.end_x -= TILE_W;
	draw_line(&v->data, v->line, color);
	v->line.end_x += TILE_W / 2;
	v->line.end_y = v->line.begin_y + TILE_H / 2;
	draw_line(&v->data, v->line, color);
}

void	draw_block(t_vars *v, int x, int y, int z)
{
	int	color;

	color = 0xFFFFFF;
	v->line.begin_x = W_WIDTH / 2 + ((TILE_W / 2) * (x - y));
	v->line.begin_y = (TILE_H * 3 / 2) + (TILE_H / 2 * (x + y)) - (z * TILE_H);
	v->line.end_x = v->line.begin_x - (TILE_W / 2);
	v->line.end_y = v->line.begin_y + (TILE_H / 2);
	draw_line(&v->data, v->line, color);
	v->line.end_x += TILE_W;
	draw_line(&v->data, v->line, color);
	v->line.begin_y += TILE_H;
	draw_line(&v->data, v->line, color);
	v->line.end_x -= TILE_W;
	draw_line(&v->data, v->line, color);
	draw_left_and_right(v, x, y);
}
