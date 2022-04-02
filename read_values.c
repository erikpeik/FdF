/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_values.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emende <emende@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 13:08:03 by emende            #+#    #+#             */
/*   Updated: 2022/04/02 13:27:03 by emende           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
	points = (int **) malloc(sizeof(int *) * row);
	i = 0;
	while (i < row)
	{
		if (get_next_line(fd, &line) < 1)
			panic("error: get_next_line broken\n", NULL);
		splits = ft_strsplit((char const *) line, ' ');
		ft_strdel(&line);
		points[i] = atoi_splits(splits, col);
		free_strarr(splits);
		i++;
	}
	return (points);
}

int	**read_values(int fd, char *argv, t_vars *v)
{
	int		**points;


	update_count(&v->row_count, &v->col_count, fd);
	points = altitudes_to_array(v->row_count, v->col_count, argv);
	return (points);
}
