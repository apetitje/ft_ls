# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/09 17:41:11 by apetitje          #+#    #+#              #
#    Updated: 2017/01/17 11:24:44 by apetitje         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls
SRC = ft_ls.c ele_func.c flag_func.c ft_list_sort.c print_func.c free_func.c stat_func.c list_sort_insert.c print_long.c dir_func.c size_func.c
LIB = ./libft
INC = $(LIB)/inc/
CC = clang
CFLAGS = -Wall -Wextra -Werror -I$(LIB) -I$(INC)
DOSLIB = -L $(LIB) -l ftprintf
COMPILLIB = $(MAKE) -C ./libft
OBJ = $(SRC:.c=.o)
DEPEND = $(SRC:.c=.d)

all : $(NAME)

$(NAME) :	$(OBJ) 
	$(COMPILLIB)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(DOSLIB)

%.o:%.c
	$(CC) $(CFLAGS) -MMD -c $< -o $@

clean :
	$(MAKE) -C $(LIB) clean
	/bin/rm -f $(OBJ) $(DEPEND)

fclean : clean
	/bin/rm -f $(NAME)
	/bin/rm -f $(LIB)/libftprintf.a

re : fclean all

-include $(OBJ:.o=.d)

.PHONY : all clean fclean re
