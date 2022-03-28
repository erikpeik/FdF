/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emende <emende@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 23:36:54 by emende            #+#    #+#             */
/*   Updated: 2022/03/28 17:55:09 by emende           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	flatSlope(t_data *img, t_line line, int delta_x, int delta_y)
{
	int	decision;
	int	i;

	decision = 2 * delta_y - delta_x;
	i = 0;
	while (i <= delta_x)
	{
		if (line.begin_x < line.end_x)
			line.begin_x += 1;
		else
			line.begin_x -= 1;
		if (decision < 0)
		{
			ft_mlx_pixel_put(img, line.begin_x, line.begin_y, 0xFF0000); // RED
			decision = decision + 2 * delta_y;
		}
		else
		{
			if (line.begin_y < line.end_y)
				line.begin_y += 1;
			else
				line.begin_y -= 1;
			ft_mlx_pixel_put(img, line.begin_x, line.begin_y, 0x00FFFF); // RED
			decision = decision + 2 * delta_y - 2 * delta_x;
		}
		i++;
	}
}

void	steepSlope(t_data *img, t_line line, int delta_x, int delta_y)
{
	int	decision;
	int	i;

	decision = 2 * delta_y - delta_x;
	i = 0;
	while (i <= delta_x)
	{
		if (line.begin_x < line.end_x)
			line.begin_x += 1;
		else
			line.begin_x -= 1;
		if (decision < 0)
		{
			ft_mlx_pixel_put(img, line.begin_y, line.begin_x, 0xFF0000); // RED
			decision = decision + 2 * delta_y;
		}
		else
		{
			if (line.begin_y < line.end_y)
				line.begin_y += 1;
			else
				line.begin_y -= 1;
			ft_mlx_pixel_put(img, line.begin_y, line.begin_x, 0x00FFFF); // RED
			decision = decision + 2 * delta_y - 2 * delta_x;
		}
		i++;
	}
}

void	draw_line(t_data *img, t_line line, int color)
{
	int	delta_x;
	int	delta_y;

	delta_x = ft_abs(line.end_x - line.begin_x);
	delta_y = ft_abs(line.end_y - line.begin_y);
	if (delta_x > delta_y)
		flatSlope(img, line, delta_x, delta_y);
	else
		steepSlope(img, line, delta_x, delta_y);
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
