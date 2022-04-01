/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emende <emende@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 15:33:14 by emende            #+#    #+#             */
/*   Updated: 2022/04/01 19:03:48 by emende           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	panic(char	*msg, t_vars *v)
{
	ft_putstr_fd(msg, 2);
	if (v)
	{
		if (v->mlx_ptr && v->data.img)
			mlx_destroy_image(v->mlx_ptr, v->data.img);
		if (v->mlx_ptr && v->win_ptr)
			mlx_destroy_window(v->mlx_ptr, v->win_ptr);
		if (v)
			free(v);
	}
	exit (0);
}

int	hook_key(int keycode, t_vars *v)
{
	ft_putnbr(keycode);
	ft_putchar('\n');
	if (keycode == 53)
		panic("", v);
	return (0);
}
