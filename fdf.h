/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emende <emende@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 20:26:51 by emende            #+#    #+#             */
/*   Updated: 2022/03/30 20:06:20 by emende           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include "mlx.h"
# include <math.h>

# define W_WIDTH 300
# define W_HEIGHT 300

typedef struct s_data {
	void	*img;
	void	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}				t_data;

typedef struct s_line {
	int	begin_x;
	int	begin_y;
	int	end_x;
	int	end_y;
	int	delta_x;
	int	delta_y;
}				t_line;

void	ft_mlx_pixel_put(t_data *data, int x, int y, int color);
void	draw_line(t_data *img, t_line line, int color);

#endif
