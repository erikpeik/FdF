/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emende <emende@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 15:36:24 by emende            #+#    #+#             */
/*   Updated: 2022/03/29 10:55:22 by emende           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(void)
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_data	img;
	t_line	line;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, W_WIDTH, W_HEIGHT, "FdF");
	img.img = mlx_new_image(mlx_ptr, W_WIDTH, W_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_len, &img.endian);
	line.begin_x = 0;
	line.begin_y = W_HEIGHT/2;
	line.end_x = W_WIDTH;
	line.end_y =  W_HEIGHT/2 - 100;
	draw_line(&img, line, 0xFFFFFF);
//	ft_mlx_pixel_put(&img, 0, 0, 0xFFFFFF);
//	mlx_pixel_put(mlx_ptr, win_ptr, 800/2, 500/2, 0xFrFFFFF);
	mlx_put_image_to_window(mlx_ptr, win_ptr, img.img, 0, 0);
	mlx_loop(mlx_ptr);

//	mlx_destroy_image(mlx_ptr, img.img);
//	mlx_destroy_window(mlx_ptr, win_ptr);
//	free(mlx_ptr);
	return (0);
}
