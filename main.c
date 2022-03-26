/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emende <emende@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 15:36:24 by emende            #+#    #+#             */
/*   Updated: 2022/03/26 23:41:48 by emende           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(void)
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_data	img;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 800, 500, "FdF");
	img.img = mlx_new_image(mlx_ptr, 800, 500);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_len, &img.endian);
	ft_mlx_pixel_put(&img, 0, 0, 0xFFFFFF);
//	mlx_pixel_put(mlx_ptr, win_ptr, 800/2, 500/2, 0xFFFFFF);
	mlx_put_image_to_window(mlx_ptr, win_ptr, img.img, 400, 250);
	mlx_loop(mlx_ptr);
	return (0);
}
