/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emende <emende@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 12:12:27 by emende            #+#    #+#             */
/*   Updated: 2022/04/04 12:14:10 by emende           ###   ########.fr       */
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
			ft_mlx_pixel_put(&v->data, col, row, 0);
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
	projection(v);
	mlx_put_image_to_window(v->mlx_ptr, v->win_ptr, v->data.img, 0, 0);
	mlx_string_put(v->mlx_ptr, v->win_ptr, 20, 20, 0xFFFFFF, "Move: Arrows");
	mlx_string_put(v->mlx_ptr, v->win_ptr, 20, 40, 0xFFFFFF, "Flatten: -/+");
	mlx_string_put(v->mlx_ptr, v->win_ptr, 20, 60, 0xFFFFFF, "Zoom: A/S");
	mlx_string_put(v->mlx_ptr, v->win_ptr, 20, 80, 0xFFFFFF, "Projection: 1-3");
}
