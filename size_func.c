/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/15 18:15:51 by apetitje          #+#    #+#             */
/*   Updated: 2017/01/15 18:17:08 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	init_size(t_size *size)
{
	size->total_blocks = 0;
	size->uid = 0;
	size->gid = 0;
	size->lnk = 0;
	size->name = 0;
	size->major = 0;
	size->minor = 0;
}

void	fill_size(t_list *p, t_size *size)
{
	size_t	tmp;

	while (p)
	{
		size->total_blocks += ((t_f *)p->data)->stt.st_blocks;
		if (size->uid < ((t_f *)p->data)->uid_len)
			size->uid = ((t_f *)p->data)->uid_len;
		if (size->gid < ((t_f *)p->data)->gid_len)
			size->gid = ((t_f *)p->data)->gid_len;
		tmp = ft_ilen(((t_f *)p->data)->stt.st_nlink);
		if (size->lnk < tmp)
			size->lnk = tmp;
		tmp = ft_ilen(((t_f *)p->data)->stt.st_size);
		if (size->name < tmp)
			size->name = tmp;
		if (((t_f *)p->data)->type == 'c' || ((t_f *)p->data)->type == 'b')
		{
			if (size->major < ft_ilen(major(((t_f *)p->data)->stt.st_rdev)))
				size->major = ft_ilen(major(((t_f *)p->data)->stt.st_rdev));
			if (size->minor < ft_ilen(minor(((t_f *)p->data)->stt.st_rdev)))
				size->minor = ft_ilen(minor(((t_f *)p->data)->stt.st_rdev));
		}
		p = p->next;
	}
}
