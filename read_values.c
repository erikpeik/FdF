/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_values.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emende <emende@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 13:08:03 by emende            #+#    #+#             */
/*   Updated: 2022/04/04 11:58:13 by emende           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	update_count(t_vars *v, int fd, int ret)
{
	char	*line;
	char	**split;

	v->row_count = 0;
	ret = get_next_line(fd, &line);
	if (ret < 1)
		panic("error: File was empty or directory\n", v);
	split = ft_strsplit(line, ' ');
	free(line);
	v->col_count = (int) ft_arrlen((const void **) split) - 1;
	free_strarr(split);
	while (ret)
	{
		ret = get_next_line(fd, &line);
		if (ret)
		{
			split = ft_strsplit((char const *) line, ' ');
			ft_strdel(&line);
			free_strarr(split);
			if ((ft_arrlen((const void **) split) - 1) != (size_t) v->col_count)
				panic("error: Differences on lines.\n", v);
		}
		v->row_count++;
	}
	close(fd);
}

static int	*atoi_splits(char **splits, int col)
{
	int	*split;
	int	i;

	split = (int *) malloc(sizeof(int) * (size_t)(col + 1));
	i = 0;
	while (i <= col)
	{
		split[i] = ft_atoi(splits[i]);
		i++;
	}
	return (split);
}

static int	**altitudes_to_array(int row, int col, char *argv)
{
	int		fd;
	char	*line;
	int		**points;
	char	**splits;
	int		i;

	fd = open(argv, O_RDONLY);
	if (fd < 0)
		panic("error: Open failed.\n", NULL);
	points = (int **) malloc(sizeof(int *) * (size_t)row);
	i = 0;
	while (i < row)
	{
		if (get_next_line(fd, &line) < 1)
			panic("error: get_next_line error\n", NULL);
		splits = ft_strsplit((char const *) line, ' ');
		ft_strdel(&line);
		points[i] = atoi_splits(splits, col);
		free_strarr(splits);
		i++;
	}
	close(fd);
	return (points);
}

static void	count_altitudes(t_vars *v, int **points)
{
	int	row;
	int	col;

	v->max_altitude = points[0][0];
	v->min_altitude = points[0][0];
	row = -1;
	while (++row < v->row_count)
	{
		col = -1;
		while (++col < v->col_count)
		{
			if (points[row][col] > v->max_altitude)
				v->max_altitude = points[row][col];
			if (points[row][col] > v->max_altitude)
				v->min_altitude = points[row][col];
		}
	}
}

int	**read_values(int fd, char *argv, t_vars *v)
{
	int		**points;

	update_count(v, fd, 0);
	points = altitudes_to_array(v->row_count, v->col_count, argv);
	count_altitudes(v, points);
	ft_putnbr(v->max_altitude);
	ft_putchar('\n');
	ft_putnbr(v->min_altitude);
	ft_putchar('\n');
	return (points);
}
