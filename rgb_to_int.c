/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_to_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emende <emende@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 22:59:15 by emende            #+#    #+#             */
/*   Updated: 2022/03/26 23:41:26 by emende           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	rgb_to_int2(double r, double g, double b)
{
	int	color;

	color = 0;
	color |= (int )(b * 255);
	color |= (int )(g * 255);
	color |= (int )(r * 255);
	return (color);
}

int	rgb_to_int(double r, double g, double b)
{
	int	color;

	color = 0;
	color += (int)(r) << 16;
	color += (int)(g) << 8;
	color += b;
	return (color);
}

int	main(void)
{
	int	color;

	color = rgb_to_int(255, 50, 0);
	printf("%d\n", color);
	color = rgb_to_int2(255, 50, 0);
	printf("%d\n", color);
	return (0);
}
