/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_values.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emende <emende@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 13:08:03 by emende            #+#    #+#             */
/*   Updated: 2022/04/04 16:11:26 by emende           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	update_count(t_vars *v, int fd, int ret, char *line)
{
	ret = get_next_line(fd, &line);
	if (ret < 1)
		panic("error: File was empty or directory\n", v);
	v->split = ft_strsplit(line, ' ');
	if (!v->split)
		panic("error: malloc failed.\n", v);
	ft_strdel(&line);
	v->col_count = (int) ft_arrlen((const void **) v->split) - 1;
	free_strarr(v->split);
	while (ret)
	{
		ret = get_next_line(fd, &line);
		if (ret)
		{
			v->split = ft_strsplit((char const *) line, ' ');
			if (!v->split)
				panic("error: malloc failed.\n", v);
			ft_strdel(&line);
			free_strarr(v->split);
			if ((ft_arrlen((const void **) v->split) - 1)
				!= (size_t) v->col_count)
				panic("error: Differences on lines.\n", v);
		}
		v->row_count++;
	}
}

static int	*atoi_splits(char **splits, int col)
{
	int	*split;
	int	i;

	split = (int *) malloc(sizeof(int) * (size_t)(col + 1));
	if (!split)
		panic("error: malloc failed\n", NULL);
	i = 0;
	while (i <= col)
	{
		split[i] = ft_atoi(splits[i]);
		i++;
	}
	return (split);
}

static int	**altitudes_to_array(t_vars *v, int fd)
{
	char	*line;
	int		**points;
	char	**splits;
	int		i;

	points = (int **) malloc(sizeof(int *) * (size_t)v->row_count);
	if (!points)
		panic("error: malloc fail.\n", v);
	i = 0;
	while (i < v->row_count)
	{
		if (get_next_line(fd, &line) < 1)
			panic("error: get_next_line error\n", v);
		splits = ft_strsplit((char const *) line, ' ');
		if (!splits)
			panic("error: ft_strsplit failed.\n", v);
		ft_strdel(&line);
		points[i] = atoi_splits(splits, v->col_count);
		if (!(points[i]) && free_intarr(points, i) && free_strarr(splits))
			panic("error: malloc failed.\n", v);
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
	char	*line;

	line = NULL;
	update_count(v, fd, 0, line);
	close(fd);
	fd = open(argv, O_RDONLY);
	if (fd < 0)
		panic("error: Open failed.\n", v);
	points = altitudes_to_array(v, fd);
	count_altitudes(v, points);
	return (points);
}
