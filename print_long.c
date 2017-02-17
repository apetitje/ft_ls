/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_long.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/15 18:13:33 by apetitje          #+#    #+#             */
/*   Updated: 2017/01/15 18:17:29 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static size_t	follow_link(t_list *ptr, char link[1024])
{
	size_t		ret;

	ret = 0;
	if (((t_f *)ptr->data)->type == 'l')
	{
		ret = readlink(((t_f *)ptr->data)->path, link + 1, 1023);
		link[0] = '/';
		link[ret + 1] = '\0';
	}
	return (ret);
}

static char		*get_time(t_flag *flag, time_t *tim_spec, t_f *ele, int *tprec)
{
	char	*tim;

	if (flag->c)
		*tim_spec = ele->stt.st_ctimespec.tv_sec;
	else if (flag->u)
		*tim_spec = ele->stt.st_atimespec.tv_sec;
	else if (flag->u_maj)
		*tim_spec = ele->stt.st_birthtimespec.tv_sec;
	else
		*tim_spec = ele->stt.st_mtimespec.tv_sec;
	tim = ctime(tim_spec);
	if (tim[25])
	{
		ft_memmove(tim + 20, tim + 24, 5);
		*tprec = 6;
	}
	else if (flag->t_maj)
		*tprec = 8;
	else
		*tprec = 5;
	return (tim);
}

static void		long_first(t_f *ele, t_size size)
{
	char		acc[12];

	access_char(ele, acc);
	ft_printf("%-11s %*lu %-*s%-*s", acc, size.lnk, ele->stt.st_nlink,
			size.uid + ((size.gid && size.uid) ? 2 : 0),
			ele->uid_name, size.gid + 2, ele->gr_name);
}

static void		long_last(t_f *ele, t_flag *flag)
{
	int			timprec;
	time_t		tim_spec;
	char		*tim;
	time_t		t_loc;

	tim = get_time(flag, &tim_spec, ele, &timprec);
	ft_printf(" %.3s %.2s %.*s %-*.4s%s", tim + 4, tim + 8, timprec, ((tim_spec
			< time(&t_loc) - 15768000 || tim_spec > time(&t_loc) + 15768000)
				? tim + 19 : tim + 11), ((flag->t_maj) ? 5 : 0),
				((flag->t_maj) ? tim + 20 : ""), ele->name);
}

void			print_long(t_list *ptr, t_flag *flag)
{
	t_size		size;
	char		link[1024];
	size_t		ret;

	init_size(&size);
	fill_size(ptr, &size);
	if (ptr && ((t_f *)ptr->data)->path_len > ((t_f *)ptr->data)->name_len)
		ft_printf("total %lu\n", size.total_blocks);
	while (ptr)
	{
		ret = 0;
		long_first(((t_f *)ptr->data), size);
		ret = follow_link(ptr, link);
		if (((t_f *)ptr->data)->type == 'c' || ((t_f *)ptr->data)->type == 'b')
			ft_printf("%*d, %*d", size.major,
					major(((t_f *)ptr->data)->stt.st_rdev), size.minor,
					minor(((t_f *)ptr->data)->stt.st_rdev));
		else
			ft_printf("%*u", size.name, ((t_f *)ptr->data)->stt.st_size);
		long_last((t_f *)ptr->data, flag);
		if (ret)
			ft_printf(" -> %s", link + 1);
		write(1, "\n", 1);
		ptr = ptr->next;
	}
}
