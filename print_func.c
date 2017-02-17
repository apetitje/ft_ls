/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/08 20:57:53 by apetitje          #+#    #+#             */
/*   Updated: 2017/02/10 14:52:48 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		print_commas(t_list *lst, t_winsize ws, int code)
{
	int			len;

	len = 0;
	while (lst != NULL)
	{
		if (lst->next)
			len += ft_printf("%s, ", ((t_f *)lst->data)->name);
		else
			ft_printf("%s", ((t_f *)lst->data)->name);
		lst = lst->next;
		if (len >= ws.ws_col
			|| (lst && len + ((t_f *)lst->data)->name_len + 1 >= ws.ws_col - 1))
		{
			write(1, "\n", 1);
			len = 0;
		}
	}
	if (code == 2)
		write(1, ",", 1);
}

static void		print_coldown(t_list *lst, int nb_col, size_t size, int nb_ele)
{
	int			i;
	int			j;
	t_list		*p;
	int			ele_by_col;

	i = -1;
	j = 1;
	ele_by_col = nb_ele / nb_col + ((nb_ele % nb_col > 0) ? 1 : 0);
	while (nb_ele > 0)
	{
		p = ft_list_at(lst, j + (++i * ele_by_col));
		if (p)
		{
			ft_printf("%-*s",
					((i < nb_col - 1) ? size : 0), ((t_f *)p->data)->name);
			--nb_ele;
		}
		if ((i >= nb_col - 1 && nb_ele != 0) || !p)
		{
			write(1, "\n", 1);
			i = -1;
			++j;
		}
	}
}

static void		print_colacross(t_list *lst, int nb_col,
		size_t size, int nb_ele)
{
	int		i;

	while (nb_ele > 0)
	{
		i = nb_col;
		while (nb_ele > 0 && i > 0)
		{
			ft_printf("%-*s ", size - 1, ((t_f *)lst->data)->name);
			lst = lst->next;
			--i;
			--nb_ele;
		}
		if (i == 0)
			write(1, "\n", 1);
	}
}

static void		print_col(t_winsize ws, t_list *lst, t_flag *flag)
{
	t_list		*ptr;
	size_t		size;
	int			nb_col;
	int			nb_ele;

	ptr = lst;
	size = 0;
	ft_list_index(&lst);
	while (ptr != NULL)
	{
		if (((t_f *)ptr->data)->name_len + 1 > size)
			size = ((t_f *)ptr->data)->name_len + 1;
		if (!ptr->next)
			nb_ele = ptr->index;
		ptr = ptr->next;
	}
	nb_col = ws.ws_col / size;
	if (flag->col_down)
		print_coldown(lst, nb_col, size, nb_ele);
	else
		print_colacross(lst, nb_col, size, nb_ele);
}

void			print(t_list *lst, t_flag *flag, int code)
{
	t_winsize	ws;

	if (!lst)
		return ;
	type_char(lst);
	if (flag->l)
		print_long(lst, flag);
	else if ((isatty(1) || flag->col_forced || flag->commas) && !flag->one_col)
	{
		ioctl(0, TIOCGWINSZ, &ws);
		if (flag->commas)
			print_commas(lst, ws, code);
		else if (flag->col_down || flag->col_across)
			print_col(ws, lst, flag);
		write(1, "\n", 1);
	}
	else if ((!isatty(1) && !flag->col_forced && !flag->commas)
			|| flag->one_col)
	{
		while (lst != NULL)
		{
			ft_printf("%s\n", ((t_f *)lst->data)->name);
			lst = lst->next;
		}
	}
}
