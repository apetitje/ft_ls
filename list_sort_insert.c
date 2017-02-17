/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_sort_insert.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 15:01:15 by apetitje          #+#    #+#             */
/*   Updated: 2017/01/15 17:12:53 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	list_revsort_insert(t_list **begin_list, t_list *new,
		int (*f)(const char *, const char *))
{
	t_list	*ptr;

	ptr = *begin_list;
	if (ft_strcmp(((t_f *)ptr->data)->name, ((t_f *)new->data)->name) < 0)
	{
		new->next = ptr;
		ptr->prev = new;
		*begin_list = new;
	}
	else
	{
		while (ptr->next && (f)(((t_f *)ptr->next->data)->name,
					((t_f *)new->data)->name) >= 0)
			ptr = ptr->next;
		new->next = ptr->next;
		ptr->next = new;
		new->prev = ptr;
	}
}

static void	list_sort_ins(t_list **begin_list, t_list *new,
		int (*f)(const char *, const char *))
{
	t_list	*ptr;

	ptr = *begin_list;
	if ((f)(((t_f *)ptr->data)->name, ((t_f *)new->data)->name) > 0)
	{
		new->next = ptr;
		ptr->prev = new;
		*begin_list = new;
	}
	else
	{
		while (ptr->next && (f)(((t_f *)ptr->next->data)->name,
					((t_f *)new->data)->name) <= 0)
			ptr = ptr->next;
		new->next = ptr->next;
		ptr->next = new;
		new->prev = ptr;
	}
}

void		list_sort_insert(t_list **begin_list, t_list *new, t_flag flag)
{
	if (begin_list && new)
	{
		if (!*begin_list)
			*begin_list = new;
		else if (flag.no_sort)
			ft_lstaddback(begin_list, new);
		else if (flag.r_sort)
			list_revsort_insert(begin_list, new, &ft_strcmp);
		else
			list_sort_ins(begin_list, new, &ft_strcmp);
	}
}
