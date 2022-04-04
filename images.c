/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emende <emende@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 12:12:27 by emende            #+#    #+#             */
/*   Updated: 2022/04/04 17:15:52 by emende           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
			ft_mlx_pixel_put(&v->data, col, row, v->colormode[v->light_switch]);
			col++;
		}
		row++;
	}
}

void	refresh(t_vars *v)
{
	clear_image(v);
	image_to_display(v);
}

void	image_to_display(t_vars *v)
{
	int	color;

	if (v->light_switch == 0)
		color = v->colormode[1];
	else
		color = v->colormode[0];
	projection(v);
	mlx_put_image_to_window(v->mlx_ptr, v->win_ptr, v->data.img, 0, 0);
	mlx_string_put(v->mlx_ptr, v->win_ptr, 20, 20, color, "Move: Arrows");
	mlx_string_put(v->mlx_ptr, v->win_ptr, 20, 40, color, "Flatten: -/+");
	mlx_string_put(v->mlx_ptr, v->win_ptr, 20, 60, color, "Zoom: A/S");
	mlx_string_put(v->mlx_ptr, v->win_ptr, 20, 80, color, "Projection: 1-3");
	mlx_string_put(v->mlx_ptr, v->win_ptr, 20, 100, color, "Colors: c");
	mlx_string_put(v->mlx_ptr, v->win_ptr, 20, 120, color, "Light mode: L");
}
