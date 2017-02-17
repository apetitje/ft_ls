/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 16:10:02 by apetitje          #+#    #+#             */
/*   Updated: 2017/01/15 18:19:56 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <sys/ioctl.h>
# include <stdlib.h>
# include <stdio.h>
# include <dirent.h>
# include <unistd.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/xattr.h>
# include <pwd.h>
# include <uuid/uuid.h>
# include <grp.h>
# include <uuid/uuid.h>
# include <time.h>
# include <sys/errno.h>
# include <sys/acl.h>
# include "ft_printf.h"

typedef struct dirent	t_dirent;
typedef struct stat		t_stat;
typedef struct winsize	t_winsize;
typedef struct passwd	t_passwd;
typedef struct group	t_group;
typedef struct timespec	t_timespec;

typedef struct			s_flag
{
	int					c;
	int					n;
	int					o;
	int					g;
	int					t;
	int					u;
	int					color;
	int					u_maj;
	int					t_maj;
	int					d_plain;
	int					no_sort;
	int					is_exec;
	int					one_col;
	int					col_down;
	int					col_forced;
	int					col_across;
	int					rec;
	int					commas;
	int					l;
	int					slash;
	int					file_types;
	int					hidden;
	int					root;
	int					r_sort;
	int					size_sort;
}						t_flag;

typedef struct			s_f
{
	char				type;
	char				type_c;
	size_t				name_len;
	size_t				uid_len;
	size_t				gid_len;
	size_t				path_len;
	char				*path;
	char				*name;
	char				*gr_name;
	char				*uid_name;
	t_stat				stt;
}						t_f;

typedef struct			s_size
{
	quad_t				total_blocks;
	size_t				uid;
	size_t				gid;
	size_t				name;
	size_t				lnk;
	size_t				major;
	size_t				minor;
}						t_size;

char					get_acl(char *path, ssize_t attr);
void					list_sort_insert(t_list **begin_list, t_list *new,
							t_flag flag);
void					free_lst(t_list **lst);
void					print(t_list *lst, t_flag *flag, int code);
void					ft_list_sort(t_list **begin_list, t_flag flag);
char					f_type(t_stat stat);
void					access_char(t_f *ele, char acc[12]);
void					ft_init_flag(t_flag *flag);
void					ft_flag(char c, t_flag *flag);
t_f						*new_file(char *name, char *path, t_flag *flag);
void					type_char(t_list *lst);
void					read_dir(t_list *lst, char *dir_name, t_flag flag,
							int code);
void					print_long(t_list *ptr, t_flag *flag);
void					fill_size(t_list *p, t_size *size);
void					init_size(t_size *size);
void					read_dir(t_list *lst, char *dir_name,
							t_flag flag, int code);

#endif
