/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emende <emende@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 20:26:51 by emende            #+#    #+#             */
/*   Updated: 2022/04/02 20:09:34 by emende           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include "mlx.h"
# include "get_next_line.h"
# include <math.h>
# include <fcntl.h>

# define W_WIDTH 2000
# define W_HEIGHT 1200

# define TILE_W 100
# define TILE_H 50

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

typedef struct s_vars {
	void			*mlx_ptr;
	void			*win_ptr;
	int				row_count;
	int				col_count;
	int				max_altitude;
	int				min_altitude;
	struct s_line	line;
	struct s_data	data;
	int				**points;
}				t_vars;

void	ft_mlx_pixel_put(t_data *data, int x, int y, int color);
void	draw_line(t_data *img, t_line line, int color);
int		hook_key(int keycode, t_vars *v);
void	panic(char	*msg, t_vars *v);
int		**read_values(int fd, char *argv, t_vars *v);

void	draw_tile(t_vars *v, int x, int y, int color);
void	draw_block(t_vars *v, int x, int y, int z);

int		free_intarr(int **split, int length);
int		free_strarr(char **split);

#endif
