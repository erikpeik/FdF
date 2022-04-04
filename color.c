/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emende <emende@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 16:25:51 by emende            #+#    #+#             */
/*   Updated: 2022/04/04 18:10:18 by emende           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	initilize_colors(t_vars *v)
{
	v->color_theme = 1;
	v->colors[0][0] = 0xf4b41a;
	v->colors[0][1] = 0x143d59;
	v->colors[1][0] = 0xe71989;
	v->colors[1][1] = 0xffe042;
	v->colors[2][0] = 0xed335f;
	v->colors[2][1] = 0xf9858b;
	v->colors[3][0] = 0x603601;
	v->colors[3][1] = 0xebc999;
	v->colors[4][0] = 0x22577e;
	v->colors[4][1] = 0x999999;
	v->light_switch = 0;
	v->colormode[0] = 0x121212;
	v->colormode[1] = 0xececec;
}
