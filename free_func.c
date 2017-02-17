/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/08 22:04:53 by apetitje          #+#    #+#             */
/*   Updated: 2017/01/15 17:00:47 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	free_file(t_f *file)
{
	free(file->path);
	free(file->name);
	if (file->gr_name)
		free(file->gr_name);
	if (file->uid_name)
		free(file->uid_name);
	free(file);
}

void		free_lst(t_list **lst)
{
	t_list *ptr;

	ptr = *lst;
	while (ptr)
	{
		free_file(((t_f *)ptr->data));
		free(ptr);
		ptr = ptr->next;
	}
	*lst = NULL;
}
