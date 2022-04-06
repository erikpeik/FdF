/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_endl.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emende <emende@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 19:55:40 by emende            #+#    #+#             */
/*   Updated: 2022/04/06 16:48:34 by emende           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ft_putnbr(), but with newline at end */

#include "libft.h"

void	ft_putnbr_endl(int n)
{
	if (n == -2147483648)
		ft_putstr("-2147483648");
	else if (n < 0)
	{
		ft_putchar('-');
		ft_putnbr(-n);
	}
	else if (n > 9)
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
	else
		ft_putchar((char ) n + '0');
	ft_putchar('\n');
}
