/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stat_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 16:34:29 by apetitje          #+#    #+#             */
/*   Updated: 2017/01/15 16:37:34 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char		f_type(t_stat stat)
{
	if ((stat.st_mode & S_IFMT) == S_IFLNK)
		return ('l');
	if ((stat.st_mode & S_IFMT) == S_IFDIR)
		return ('d');
	if ((stat.st_mode & S_IFMT) == S_IFREG)
		return ('f');
	if ((stat.st_mode & S_IFMT) == S_IFIFO)
		return ('p');
	if ((stat.st_mode & S_IFMT) == S_IFSOCK)
		return ('s');
	if ((stat.st_mode & S_IFMT) == S_IFBLK)
		return ('b');
	if ((stat.st_mode & S_IFMT) == S_IFCHR)
		return ('c');
	if ((stat.st_mode & S_IFMT) == S_IFWHT)
		return ('W');
	return (0);
}

char		get_acl(char *path, ssize_t attr)
{
	acl_t	acl;
	int		ret;

	ret = 0;
	if ((acl = acl_get_file(path, ACL_TYPE_EXTENDED)))
		ret = 1;
	acl_free((void *)acl);
	if (attr > 0)
		return ('@');
	else if (ret)
		return ('+');
	return ('\0');
}

static void	other_stat(t_stat stat, char acc[12])
{
	if (stat.st_mode & S_IROTH)
		acc[7] = 'r';
	else
		acc[7] = '-';
	if (stat.st_mode & S_IWOTH)
		acc[8] = 'w';
	else
		acc[8] = '-';
	if ((stat.st_mode & S_IXOTH) && (stat.st_mode & (S_ISVTX)))
		acc[9] = 't';
	else if (stat.st_mode & S_IXOTH)
		acc[9] = 'x';
	else if (stat.st_mode & S_ISVTX)
		acc[9] = 'T';
	else
		acc[9] = '-';
}

static void	group_stat(t_stat stat, char acc[12])
{
	if (stat.st_mode & S_IRGRP)
		acc[4] = 'r';
	else
		acc[4] = '-';
	if (stat.st_mode & S_IWGRP)
		acc[5] = 'w';
	else
		acc[5] = '-';
	if (!(stat.st_mode & S_IXUSR) && (stat.st_mode & S_ISGID))
		acc[6] = 'S';
	else if (stat.st_mode & S_IXGRP)
	{
		if (stat.st_mode & S_ISGID)
			acc[6] = 's';
		else
			acc[6] = 'x';
	}
	else
		acc[6] = '-';
}

void		access_char(t_f *ele, char acc[12])
{
	acc[11] = '\0';
	acc[0] = (ele->type == 'f') ? '-' : ele->type;
	if (ele->stt.st_mode & S_IRUSR)
		acc[1] = 'r';
	else
		acc[1] = '-';
	if (ele->stt.st_mode & S_IWUSR)
		acc[2] = 'w';
	else
		acc[2] = '-';
	if (!(ele->stt.st_mode & S_IXUSR) && (ele->stt.st_mode & S_ISUID))
		acc[3] = 'S';
	else if (ele->stt.st_mode & S_IXUSR)
	{
		if (ele->stt.st_mode & S_ISUID)
			acc[3] = 's';
		else
			acc[3] = 'x';
	}
	else
		acc[3] = '-';
	group_stat(ele->stt, acc);
	other_stat(ele->stt, acc);
	acc[10] = get_acl(ele->path, listxattr(ele->path, NULL, 0, XATTR_NOFOLLOW));
}
