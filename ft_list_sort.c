/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_sort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/02 20:24:07 by apetitje          #+#    #+#             */
/*   Updated: 2017/01/15 17:00:28 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		ft_list_sizesort(t_list **begin_list, t_flag flag)
{
	t_list	*ptr;
	int		is_sorting;
	void	*tmp;

	is_sorting = 1;
	while (is_sorting)
	{
		ptr = *begin_list;
		is_sorting = 0;
		while (ptr && ptr->next)
		{
			if ((flag.r_sort && ((t_f *)ptr->data)->stt.st_size
						> ((t_f *)ptr->next->data)->stt.st_size)
					|| ((!flag.r_sort) && ((t_f *)ptr->data)->stt.st_size
						< ((t_f *)ptr->next->data)->stt.st_size))
			{
				is_sorting = 1;
				tmp = ptr->data;
				ptr->data = ptr->next->data;
				ptr->next->data = tmp;
			}
			ptr = ptr->next;
		}
	}
}

time_t			find_time_sec(time_t *sec2, t_flag flag, t_stat stat1,
		t_stat stat2)
{
	time_t	sec1;

	if (flag.u_maj)
	{
		sec1 = stat1.st_birthtimespec.tv_sec;
		*sec2 = stat2.st_birthtimespec.tv_sec;
	}
	else if (flag.u)
	{
		sec1 = stat1.st_atimespec.tv_sec;
		*sec2 = stat2.st_atimespec.tv_sec;
	}
	else if (flag.c)
	{
		sec1 = stat1.st_ctimespec.tv_sec;
		*sec2 = stat2.st_ctimespec.tv_sec;
	}
	else
	{
		sec1 = stat1.st_mtimespec.tv_sec;
		*sec2 = stat2.st_mtimespec.tv_sec;
	}
	return (sec1);
}

static void		ft_list_timesort(t_list **begin_list, t_flag flag)
{
	t_list	*ptr;
	int		is_sorting;
	void	*tmp;
	time_t	sec1;
	time_t	sec2;

	is_sorting = 1;
	while (is_sorting)
	{
		ptr = *begin_list;
		is_sorting = 0;
		while (ptr && ptr->next)
		{
			sec1 = find_time_sec(&sec2, flag, ((t_f *)ptr->data)->stt,
					((t_f *)ptr->next->data)->stt);
			if ((flag.r_sort && sec1 > sec2) || (!flag.r_sort && sec1 < sec2))
			{
				is_sorting = 1;
				tmp = ptr->data;
				ptr->data = ptr->next->data;
				ptr->next->data = tmp;
			}
			ptr = ptr->next;
		}
	}
}

void			ft_list_sort(t_list **begin_list, t_flag flag)
{
	if (!(*begin_list) || flag.no_sort || (!flag.t && !flag.size_sort))
		return ;
	if (flag.size_sort)
		ft_list_sizesort(begin_list, flag);
	else
		ft_list_timesort(begin_list, flag);
}
