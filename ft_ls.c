/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 16:43:42 by apetitje          #+#    #+#             */
/*   Updated: 2017/02/10 14:53:01 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int				input(t_flag *flag, int argc, char **argv)
{
	int			i;
	int			j;

	i = 0;
	ft_init_flag(flag);
	while (++i < argc && argv[i][0] == '-')
	{
		j = 1;
		if (!ft_strcmp(argv[i], "--"))
			return (i + 1);
		if (!argv[i][j])
			return (i);
		while (argv[i][j])
		{
			if (!ft_strchr("1AdaCcFfGlmnopRrSTtuUxg", argv[i][j]))
			{
				ft_dprintf(2, "ft_ls: illegal option -- %c\n", argv[i][j]);
				ft_dprintf(2, "usage: ft_ls ");
				ft_dprintf(2, "[-ACFGRSTUacdfglmnoprtux1] [file ...]\n");
				exit(1);
			}
			ft_flag(argv[i][j++], flag);
		}
	}
	return (i);
}

t_list			*file_args(t_list *lst, int argc, char **argv, t_flag flag)
{
	t_stat		stt;
	int			i;

	i = 0;
	while (++i < argc)
	{
		if (argv[i] && lstat(argv[i], &stt) == -1)
		{
			if (!ft_strcmp(argv[i], ""))
			{
				ft_dprintf(2, "ft_ls: %s: %s\n", "fts_open", strerror(errno));
				exit(1);
			}
			else
				ft_dprintf(2, "ft_ls: %s: %s\n", argv[i], strerror(errno));
		}
		else if ((f_type(stt) == 'l' && ((stat(argv[i], &stt) != -1
			&& (f_type(stt) != 'd' || flag.l)) || (stat(argv[i], &stt) == -1)))
			|| (f_type(stt) == 'f' || flag.d_plain))
			list_sort_insert(&lst, ft_lstnew(new_file(argv[i], argv[i], &flag),
						sizeof(t_f *)), flag);
	}
	ft_list_sort(&lst, flag);
	print(lst, &flag, 2);
	return (lst);
}

void			dir_args(int argc, char **argv, t_flag flag, int code)
{
	int			i;
	t_stat		stt;
	char		type;
	t_list		*lst;

	lst = NULL;
	i = 0;
	if (i + 1 == argc)
		read_dir(lst, ".", flag, code);
	if (!code && i + 2 < argc)
		code = 2;
	while (++i < argc)
	{
		if (argv[i] && lstat(argv[i], &stt) != -1)
		{
			type = f_type(stt);
			if (type == 'd')
				read_dir(lst, argv[i], flag, code);
			else if ((type == 'l' && !flag.l) && (stat(argv[i], &stt) != -1
						&& (f_type(stt) == 'd')))
				read_dir(lst, argv[i], flag, code);
			code = 1;
		}
	}
}

int				main(int argc, char **argv)
{
	int			i;
	int			k;
	t_flag		flag;
	t_list		*lst;
	int			code;

	code = 0;
	lst = NULL;
	i = input(&flag, argc, argv);
	if (argv[i] && !flag.no_sort)
		ft_sort_wordtab(argv + i);
	k = i + 1;
	--i;
	if (flag.d_plain && i + 1 == argc)
		list_sort_insert(&lst, ft_lstnew(new_file(".", ".", &flag),
					sizeof(t_f *)), flag);
	if ((lst = file_args(lst, argc - i, argv + i, flag)))
		code = 1;
	if (!flag.d_plain)
		dir_args(argc - i, argv + i, flag, code);
	free_lst(&lst);
	return (0);
}
