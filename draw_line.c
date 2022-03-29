/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emende <emende@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 23:36:54 by emende            #+#    #+#             */
/*   Updated: 2022/03/29 10:56:18 by emende           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_line(t_data *img, t_line line, int color)
{
	int	delta_x;
	int	delta_y;
	int presicion;
/*	int x_ofs;
	int y_ofs; */

	delta_x = line.end_x - line.begin_x;
	delta_y = line.end_y - line.begin_y;

	presicion = 2 * delta_y - delta_x;
	while (line.begin_x < line.end_x)
	{
		if (presicion >= 0)
		{
			ft_mlx_pixel_put(img, line.begin_x, line.begin_y, color);
			line.begin_y += 1;
			presicion = presicion + 2 * delta_y - 2 * delta_x;

		}
		else
		{
			ft_mlx_pixel_put(img, line.begin_x, line.begin_y, color);
			presicion = presicion + 2 * delta_y;
		}
		line.begin_x += 1;
	}
}

/*
void	draw_line(t_data *img, t_line line, int color)
{
	double	delta_x;
	double	delta_y;
	int		pixels;
	double	pixel_x;
	double	pixel_y;

	delta_x = line.end_x - line.begin_x;
	delta_y = line.end_y - line.begin_y;
	pixels = sqrt((delta_x * delta_x) + (delta_y * delta_y));
	delta_x /= pixels;
	delta_y /= pixels;
	pixel_x = line.begin_x;
	pixel_y = line.begin_y;
	while (pixels > 0)
	{
		ft_mlx_pixel_put(img, pixel_x, pixel_y, color);
		pixel_x += delta_x;
		pixel_y += delta_y;
		pixels -= 1;
	}
}
*/
