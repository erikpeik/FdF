/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_arrays.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emende <emende@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 13:06:38 by emende            #+#    #+#             */
/*   Updated: 2022/04/09 19:27:45 by emende           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	free_strarr(char ***split)
{
	int	i;

	i = 0;
	if (split && *split)
	{
		while ((*split)[i])
		{
			free((*split)[i]);
			i++;
		}
		free(*split);
	}
	*split = NULL;
	return (1);
}

int	free_intarr(int ***split, int length)
{
	int	i;

	i = 0;
	if (split && *split)
	{
		while (i < length)
		{
			free((*split)[i]);
			i++;
		}
		free(*split);
	}
	*split = NULL;
	return (1);
}
