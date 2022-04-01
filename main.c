/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emende <emende@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 15:36:24 by emende            #+#    #+#             */
/*   Updated: 2022/04/01 21:56:08 by emende           ###   ########.fr       */
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

static int	free_strarr(char **split)
{
	int	i;

	i = 0;
	if (split)
	{
		while (split[i])
		{
			free(split[i]);
			i++;
		}
	}
	free(split);
	split = NULL;
	return (1);
}

static int	free_intarr(int **split, int length)
{
	int i;

	i = 0;
	if (split)
	{
		while (i < length)
			free(split[i++]);
		free(split);
	}
	split = NULL;
	return (1);
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
	*nums_line = (int) ft_arrlen((const void **) split) - 1;
	free_strarr(split);
	while (ret)
	{
		ret = get_next_line(fd, &line);
		if (ret)
		{
			split = ft_strsplit((char const *) line, ' ');
			ft_strdel(&line);
			free_strarr(split);
			if ((ft_arrlen((const void **) split) - 1) != (size_t) *(nums_line))
				panic("error: Differences on lines.\n", NULL);
		}
		(*row_count)++;
	}
}

static int	*atoi_splits(char **splits, int col)
{
	int	*split;
	int	i;

	split = (int *) malloc(sizeof(int) * (col + 1));
	i = 0;
	while (i <= col)
	{
		split[i] = ft_atoi(splits[i]);
		i++;
	}
	return (split);

}

static int **altitudes_to_array(int row, int col, char *argv)
{
	int		fd;
	char	*line;
	int		**points;
	char	**splits;
	int		i;
	int		ret;

	fd = open(argv, O_RDONLY);
	if (fd < 0)
		panic("error: Open failed.\n", NULL);
	points = (int **) malloc(sizeof(int *) * row);
	i = 0;
	while (i < row)
	{
		points[i] = (int *) malloc(sizeof(int) * col);
		ret = get_next_line(fd, &line);
		if (ret < 1)
			panic("error: get_next_line broken\n", NULL);
		splits = ft_strsplit((char const *) line, ' ');
		ft_strdel(&line);
		points[i] = atoi_splits(splits, col);
		free_strarr(splits);
		i++;
	}

	return (points);
}

int	**read_values(int fd, char *argv)
{
	int		**points;
	int		row_count;
	int		nums_line;

	update_count(&row_count, &nums_line, fd);
	points = altitudes_to_array(row_count, nums_line, argv);
	ft_putnbr(row_count);
	ft_putchar('\n');
	ft_putnbr(nums_line);
	ft_putchar('\n');
	system("leaks fdf");
	return (points);
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
	points = read_values(fd, argv[1]);
	free_intarr(points, 9);
	v = set_vars();
/*	draw_block(v, 0, 0, 0); */
	mlx_put_image_to_window(v->mlx_ptr, v->win_ptr, v->data.img, 0, 0);
	mlx_key_hook(v->win_ptr, hook_key, v);
	mlx_loop(v->mlx_ptr);
	return (0);
}
