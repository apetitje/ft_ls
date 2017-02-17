/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ele_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/14 17:22:42 by apetitje          #+#    #+#             */
/*   Updated: 2017/02/10 14:45:24 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		init_f(t_f *ele)
{
	ele->type_c = 0;
	ele->type = 0;
	ele->name_len = 0;
	ele->path = NULL;
	ele->name = NULL;
	ele->uid_name = NULL;
	ele->uid_len = 0;
	ele->gr_name = NULL;
	ele->gid_len = 0;
	ele->path_len = 0;
}

static void		user_group(t_f *ele, t_flag *flag)
{
	t_passwd	*pwd;
	t_group		*grp;

	if (!flag->l)
		return ;
	if (!flag->g)
	{
		if (flag->n || (pwd = getpwuid(ele->stt.st_uid)) == NULL)
			ele->uid_len = ft_asprintf(&(ele->uid_name), "%u", ele->stt.st_uid);
		else
			ele->uid_len = ft_asprintf(&(ele->uid_name), "%s", pwd->pw_name);
	}
	else
		ele->uid_name = ft_strdup("");
	if (!flag->o)
	{
		if (flag->n || (grp = getgrgid(ele->stt.st_gid)) == NULL)
			ele->gid_len = ft_asprintf(&(ele->gr_name), "%u", ele->stt.st_gid);
		else
			ele->gid_len = ft_asprintf(&(ele->gr_name), "%s", grp->gr_name);
	}
	else
		ele->gr_name = ft_strdup("");
}

static void		ele_flag(t_f *ele, t_flag *flag)
{
	if (flag->file_types)
	{
		if (ele->type == 'd')
			ele->type_c = '/';
		else if (ele->type == 'l')
			ele->type_c = '@';
		else if (ele->type == 's')
			ele->type_c = '=';
		else if (ele->type == 'W')
			ele->type_c = '%';
		else if (ele->type == 'p')
			ele->type_c = '|';
		else if (ele->stt.st_mode & S_IXUSR || ele->stt.st_mode & S_IXGRP
			|| ele->stt.st_mode & S_IXOTH)
			ele->type_c = '*';
	}
	else if (flag->slash && ele->type == 'd')
		ele->type_c = '/';
	user_group(ele, flag);
}

t_f				*new_file(char *name, char *path, t_flag *flag)
{
	t_f			*ele;

	if (!(ele = malloc(sizeof(t_f))))
		return (NULL);
	init_f(ele);
	lstat(path, &(ele->stt));
	if (f_type(ele->stt) != 'l')
	{
		if (stat(path, &(ele->stt)) == -1)
		{
			ft_dprintf(2, "ft_ls: %s: %s\n", name, strerror(errno));
			free(ele);
			return (NULL);
		}
	}
	ele->path_len = ft_asprintf(&(ele->path), "%s", path);
	ele->type = f_type(ele->stt);
	if (flag)
		ele_flag(ele, flag);
	ele->name = ft_strdup(name);
	return (ele);
}

void			type_char(t_list *lst)
{
	char		*ptr;
	int			boul;
	t_list		*p;

	boul = 0;
	p = lst;
	while (lst)
	{
		ptr = ((t_f *)lst->data)->name;
		((t_f *)lst->data)->name_len =
			ft_asprintf(&((t_f *)lst->data)->name, "%s%c",
			((t_f *)lst->data)->name, ((t_f *)lst->data)->type_c);
		if (((t_f *)lst->data)->type_c)
			((t_f *)lst->data)->name_len += 1;
		lst = lst->next;
		free(ptr);
	}
	if (boul)
	{
		while (p)
		{
			((t_f *)p->data)->name_len += 1;
			p = p->next;
		}
	}
}
