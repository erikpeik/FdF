/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emende <emende@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 15:36:24 by emende            #+#    #+#             */
/*   Updated: 2022/04/01 20:26:57 by emende           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_vars	*set_vars(void)
{
	t_vars	*v;

	v = (t_vars *) malloc(sizeof (t_vars));
	v->mlx_ptr = mlx_init();
	v->win_ptr = mlx_new_window(v->mlx_ptr, W_WIDTH, W_HEIGHT, "FdF");
	v->data.img = mlx_new_image(v->mlx_ptr, W_WIDTH, W_HEIGHT);
	v->data.addr = mlx_get_data_addr(v->data.img, &v->data.bpp, \
			&v->data.line_len, &v->data.endian);
	return (v);
}

static void	free_split(char **split)
{
	int	i;

	i = 0;
	if (split)
		while (split[i])
			free(split[i++]);
	free(split);
}

static void	update_count(int *row_count, int *nums_line, int fd)
{
	int		ret;
	char	*line;
	char	**split;

	*row_count = 0;
	ret = get_next_line(fd, &line);
	if (ret < 1)
		panic("error: File was empty or directory\n", NULL);
	split = ft_strsplit(line, ' ');
	free(line);
	*nums_line = (int) ft_arrlen((const void **) split);
	free_split(split);
	while (ret)
	{
		ret = get_next_line(fd, &line);
		if (ret)
		{
			split = ft_strsplit((char const *) line, ' ');
			ft_strdel(&line);
			free_split(split);
			if (ft_arrlen((const void **) split) != (size_t) *(nums_line))
				panic("error: Differences on lines.", NULL);
		}
		(*row_count)++;
	}
}

int	**read_values(int fd, int ret)
{
	int		**points;
	char	*line;
	int		row_count;
	int		nums_line;
	char	**split;

	update_count(&row_count, &nums_line, fd);
	ft_putnbr(row_count);
	ft_putchar('\n');
	ft_putnbr(nums_line);
	ft_putchar('\n');
/*	system("leaks fdf"); */
	return (0);
}

int	main(int argc, char **argv)
{
	t_vars	*v;
	int		**points;
	int		fd;

	if (argc != 2)
		panic("usage: ./fdf source_file\n", NULL);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		panic("error: Open failed. No such file or directory.\n", NULL);
	points = read_values(fd, 1);
	v = set_vars();
/*	draw_block(v, 0, 0, 0); */
	mlx_put_image_to_window(v->mlx_ptr, v->win_ptr, v->data.img, 0, 0);
	mlx_key_hook(v->win_ptr, hook_key, v);
	mlx_loop(v->mlx_ptr);
	return (0);
}
