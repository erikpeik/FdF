/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emende <emende@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 19:43:48 by emende            #+#    #+#             */
/*   Updated: 2022/04/01 19:48:21 by emende           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Function counts number of rows in two-dimensional array */

#include "libft.h"

size_t	ft_arrlen(const void **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}
