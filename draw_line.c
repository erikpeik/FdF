/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emende <emende@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 23:36:54 by emende            #+#    #+#             */
/*   Updated: 2022/04/04 14:21:22 by emende           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	set_offset(t_line line, int *x, int *y)
{
	if (line.delta_x < 0)
		*x = -1;
	else
		*x = 1;
	if (line.delta_y < 0)
		*y = -1;
	else
		*y = 1;
}

static void	draw_x(t_data *img, t_line line, int color)
{
	int	presicion;
	int	x_ofs;
	int	y_ofs;
	int	i;

	set_offset(line, &x_ofs, &y_ofs);
	presicion = 2 * ft_abs(line.delta_y) - ft_abs(line.delta_x);
	i = 0;
	while (i < ft_abs(line.delta_x))
	{
		if (line.x0 >= 0 && line.x0 < W_WIDTH
			&& line.y0 >= 0 && line.y0 < W_HEIGHT)
			ft_mlx_pixel_put(img, line.x0, line.y0, color);
		if (presicion < 0)
			presicion = presicion + 2 * ft_abs(line.delta_y);
		else
		{
			presicion += 2 * ft_abs(line.delta_y) - 2 * ft_abs(line.delta_x);
			line.y0 += y_ofs;
		}
		line.x0 += x_ofs;
		i++;
	}
}

static void	draw_y(t_data *img, t_line line, int color)
{
	int	presicion;
	int	x_ofs;
	int	y_ofs;
	int	i;

	set_offset(line, &x_ofs, &y_ofs);
	presicion = 2 * ft_abs(line.delta_x) - ft_abs(line.delta_y);
	i = 0;
	while (i < ft_abs(line.delta_y))
	{
		if (line.x0 >= 0 && line.x0 < W_WIDTH
			&& line.y0 >= 0 && line.y0 < W_HEIGHT)
			ft_mlx_pixel_put(img, line.x0, line.y0, color);
		if (presicion < 0)
			presicion = presicion + 2 * ft_abs(line.delta_x);
		else
		{
			presicion += 2 * ft_abs(line.delta_x) - 2 * ft_abs(line.delta_y);
			line.x0 += x_ofs;
		}
		line.y0 += y_ofs;
		i++;
	}
}

void	draw_line(t_data *img, t_line line, int color)
{
	line.delta_x = line.x1 - line.x0;
	line.delta_y = line.y1 - line.y0;
	if (ft_abs(line.delta_x) >= ft_abs(line.delta_y))
		draw_x(img, line, color);
	else
		draw_y(img, line, color);
}
