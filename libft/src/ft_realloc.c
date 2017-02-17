/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 15:50:20 by apetitje          #+#    #+#             */
/*   Updated: 2017/02/06 18:52:49 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	*ft_realloc(void *ptr, size_t size, size_t old_size)
{
	void	*dup;

	dup = NULL;
	if (size)
		if (!(dup = (char *)malloc(size)))
			return (NULL);
	if (ptr && dup)
	{
		ft_memcpy(dup, ptr, old_size);
		ft_memdel(&ptr);
	}
	(*(char *)(dup + size - 1)) = '\0';
	return (dup);
}
