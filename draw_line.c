/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emende <emende@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 23:36:54 by emende            #+#    #+#             */
/*   Updated: 2022/03/30 21:13:51 by emende           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	draw_x(t_data *img, t_line line, int color)
{
	int	presicion;
	int	x_ofs;
	int	y_ofs;

	if (line.delta_x < 0)
		x_ofs = -1;
	else
		x_ofs = 1;
	if (line.delta_y < 0)
		y_ofs = -1;
	else
		y_ofs = 1;
	presicion = 2 * ft_abs(line.delta_y) - line.delta_x;
	while (line.begin_x < line.end_x)
	{
		ft_mlx_pixel_put(img, line.begin_x, line.begin_y, color);
		if (presicion < 0)
			presicion = presicion + 2 * ft_abs(line.delta_y);
		else
		{
			presicion += 2 * ft_abs(line.delta_y) - 2 * ft_abs(line.delta_x);
			line.begin_y += y_ofs;
		}
		line.begin_x += x_ofs;
	}
}

static void draw_y(t_data *img, t_line line, int color)
{
	int	presicion;
	int	x_ofs;
	int	y_ofs;

	write(1, "y", 1);
	if (line.delta_x < 0)
		x_ofs = -1;
	else
		x_ofs = 1;
	if (line.delta_y < 0)
		y_ofs = -1;
	else
		y_ofs = 1;
	presicion = 2 * ft_abs(line.delta_x) - line.delta_y;
	while (line.begin_y < line.end_y)
	{
		ft_mlx_pixel_put(img, line.begin_x, line.begin_y, color);
		if (presicion < 0)
			presicion = presicion + 2 * ft_abs(line.delta_y);
		else
		{
			presicion += 2 * ft_abs(line.delta_x) - 2 * ft_abs(line.delta_y);
			line.begin_x += y_ofs;
		}
		line.begin_y += y_ofs;
	}
}

void	draw_line(t_data *img, t_line line, int color)
{
	line.delta_x = line.end_x - line.begin_x;
	line.delta_y = line.end_y - line.begin_y;

	if (ft_abs(line.delta_x) >= ft_abs(line.delta_y))
		draw_x(img, line, color);
	else
		draw_y(img, line, color);
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
