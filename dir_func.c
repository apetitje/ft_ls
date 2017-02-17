/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/15 18:18:48 by apetitje          #+#    #+#             */
/*   Updated: 2017/02/10 19:15:06 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_list	*ft_open_dir(DIR *rep, char *dir_nam, t_flag flag, int code)
{
	t_dirent	*file;
	char		*path;
	t_list		*lst;
	t_f			*ele;

	lst = NULL;
	path = NULL;
	while ((file = readdir(rep)))
	{
		if ((flag.hidden || *(file->d_name) != '.')
				&& (flag.root || (ft_strcmp(".", file->d_name)
						&& ft_strcmp("..", file->d_name))))
		{
			if (!ft_strcmp(dir_nam, "/"))
				ft_asprintf(&path, "%s%s", dir_nam, file->d_name);
			else
				ft_asprintf(&path, "%s/%s", dir_nam, file->d_name);
			ele = new_file(file->d_name, path, &flag);
			list_sort_insert(&lst, ft_lstnew(ele, sizeof(ele)), flag);
			free(path);
		}
	}
	ft_list_sort(&lst, flag);
	print(lst, &flag, code);
	return (lst);
}

static void		read_lst(t_list *lst, t_flag flag)
{
	t_list		*sub;
	t_list		*ptr;

	ptr = lst;
	while (lst != NULL)
	{
		sub = NULL;
		if (flag.rec && (flag.hidden || *((((t_f *)lst->data)->name)) != '.')
				&& ((t_f *)lst->data)->type == 'd'
				&& ft_strcmp(".", ((t_f *)lst->data)->name)
				&& ft_strcmp("..", ((t_f *)lst->data)->name)
				&& ft_strcmp("./", ((t_f *)lst->data)->name)
				&& ft_strcmp("../", ((t_f *)lst->data)->name))
			read_dir(sub, ((t_f *)lst->data)->path, flag, 1);
		lst = lst->next;
	}
	free_lst(&ptr);
}

void			read_dir(t_list *lst, char *dir_name, t_flag flag, int code)
{
	DIR			*rep;
	char		*tmp;

	if (code == 1)
		ft_printf("\n%s:\n", dir_name);
	else if (code == 2)
		ft_printf("%s:\n", dir_name);
	if (!(rep = opendir(dir_name)))
	{
		tmp = ft_strrchr(dir_name, '/');
		ft_dprintf(2, "ft_ls: %s: %s\n", ((tmp) ? tmp + 1 : dir_name),
				strerror(errno));
	}
	else
	{
		lst = ft_open_dir(rep, dir_name, flag, code);
		read_lst(lst, flag);
		if (closedir(rep) == -1)
		{
			tmp = ft_strrchr(dir_name, '/');
			ft_dprintf(2, "ft_ls: %s: %s\n", ((tmp) ? tmp + 1 : dir_name),
					strerror(errno));
		}
	}
}
