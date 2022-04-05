/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emende <emende@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 19:55:46 by emende            #+#    #+#             */
/*   Updated: 2021/12/10 20:16:09 by emende           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*list;
	t_list	*temp;

	list = *alst;	
	while (list)
	{
		temp = list->next;
		del(list->content, list->content_size);
		free(list);
		list = temp;
	}
	*alst = NULL;
}
