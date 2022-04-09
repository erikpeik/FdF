/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_pixel_put.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emende <emende@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 21:01:30 by emende            #+#    #+#             */
/*   Updated: 2022/04/09 22:23:02 by emende           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_mlx_pixel_put(t_vars *v, int x, int y)
{
	char	*dst;

	if (x >= 0 && x < W_WIDTH && y >= 0 && y < W_HEIGHT)
	{
		dst = v->data.addr + (y * v->data.line_len + x * (v->data.bpp / 8));
		*(unsigned int *)dst = (unsigned int) v->color;
	}
}
