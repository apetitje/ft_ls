/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/14 17:22:54 by apetitje          #+#    #+#             */
/*   Updated: 2017/01/15 18:09:57 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_init_flag(t_flag *flag)
{
	flag->c = 0;
	flag->n = 0;
	flag->o = 0;
	flag->g = 0;
	flag->t = 0;
	flag->t_maj = 0;
	flag->u = 0;
	flag->u_maj = 0;
	flag->no_sort = 0;
	flag->one_col = 0;
	flag->col_down = 1;
	flag->col_across = 0;
	flag->col_forced = 0;
	flag->rec = 0;
	flag->commas = 0;
	flag->l = 0;
	flag->slash = 0;
	flag->file_types = 0;
	flag->hidden = 0;
	flag->root = 0;
	flag->color = 0;
	flag->r_sort = 0;
	flag->size_sort = 0;
	flag->d_plain = 0;
}

static void	print_flags(char c, t_flag *flag)
{
	flag->one_col = 0;
	flag->col_across = 0;
	flag->col_down = 0;
	flag->commas = 0;
	if (c == 'C')
	{
		flag->col_forced = 1;
		flag->col_down = 1;
	}
	else if (c == 'x')
		flag->col_across = 1;
	else if (c == 'l' || c == 'g' || c == 'o' || c == 'n')
	{
		flag->l = 1;
		if (c == 'g')
			flag->g = 1;
		else if (c == 'o')
			flag->o = 1;
		else if (c == 'n')
			flag->n = 1;
	}
	else if (c == 'm')
		flag->commas = 1;
	else if (c == '1')
		flag->one_col = 1;
}

static void	sort_flags(char c, t_flag *flag)
{
	if (c == 'r')
		flag->r_sort = 1;
	else if (c == 'c' || c == 'u' || c == 'U')
	{
		flag->u = 0;
		flag->c = 0;
		flag->u_maj = 0;
		if (c == 'c')
			flag->c = 1;
		else if (c == 'u')
			flag->u = 1;
		else if (c == 'U')
			flag->u_maj = 1;
	}
	else
		flag->size_sort = 1;
}

static void	ft_flag2(char c, t_flag *flag)
{
	if (c == 't')
		flag->t = 1;
	else if (c == 'T')
		flag->t_maj = 1;
	else if (c == 'R')
		flag->rec = 1;
	else if (c == 'd')
		flag->d_plain = 1;
	else if (c == 'G')
		flag->color = 1;
}

void		ft_flag(char c, t_flag *flag)
{
	if (c == 'a' || c == 'A' || c == 'f')
	{
		if (c == 'a' || c == 'f')
			flag->root = 1;
		if (c == 'f')
			flag->no_sort = 1;
		flag->hidden = 1;
	}
	else if (ft_strchr("Cxl1mgon", c))
	{
		flag->l = 0;
		print_flags(c, flag);
	}
	else if (ft_strchr("SrcuU", c))
		sort_flags(c, flag);
	else if (c == 'F' || c == 'p')
	{
		flag->slash = 1;
		if (c == 'F')
			flag->file_types = 1;
		else
			flag->file_types = 0;
	}
	else if (ft_strchr("ntTRdG", c))
		ft_flag2(c, flag);
}
