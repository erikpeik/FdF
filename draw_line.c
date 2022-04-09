/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emende <emende@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 23:36:54 by emende            #+#    #+#             */
/*   Updated: 2022/04/09 23:00:24 by emende           ###   ########.fr       */
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

static void	draw_x(t_vars *v, int x, int y)
{
	int	presicion;
	int	x_ofs;
	int	y_ofs;
	int	i;

	set_offset(v->line, &x_ofs, &y_ofs);
	presicion = 2 * ft_abs(v->line.delta_y) - ft_abs(v->line.delta_x);
	i = 0;
	while (i < ft_abs(v->line.delta_x))
	{
		ft_mlx_pixel_put(v, x, y);
		if (presicion < 0)
			presicion = presicion + 2 * ft_abs(v->line.delta_y);
		else
		{
			presicion += 2 * ft_abs(v->line.delta_y) \
				- 2 * ft_abs(v->line.delta_x);
			y += y_ofs;
		}
		x += x_ofs;
		i++;
	}
}

static void	draw_y(t_vars *v, int x, int y)
{
	int	presicion;
	int	x_ofs;
	int	y_ofs;
	int	i;

	set_offset(v->line, &x_ofs, &y_ofs);
	presicion = 2 * ft_abs(v->line.delta_x) - ft_abs(v->line.delta_y);
	i = 0;
	while (i < ft_abs(v->line.delta_y))
	{
		ft_mlx_pixel_put(v, x, y);
		if (presicion < 0)
			presicion += 2 * ft_abs(v->line.delta_x);
		else
		{
			presicion += 2 * ft_abs(v->line.delta_x) \
				- 2 * ft_abs(v->line.delta_y);
			x += x_ofs;
		}
		y += y_ofs;
		i++;
	}
}

void	draw_line(t_vars *v)
{
	v->line.delta_x = v->line.x1 - v->line.x0;
	v->line.delta_y = v->line.y1 - v->line.y0;
	if (ft_abs(v->line.delta_x) >= ft_abs(v->line.delta_y))
		draw_x(v, v->line.x0, v->line.y0);
	else
		draw_y(v, v->line.x0, v->line.y0);
}
