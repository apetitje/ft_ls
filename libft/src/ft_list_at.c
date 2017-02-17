/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_at.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/03 16:45:06 by apetitje          #+#    #+#             */
/*   Updated: 2017/01/04 15:22:24 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_list	*ft_list_at(t_list *lst, int index)
{
	while (lst)
	{
		if (lst->index == index)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}
