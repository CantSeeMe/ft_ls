#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jye <marvin@42.fr>                         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/19 16:32:14 by jye               #+#    #+#              #
#    Updated: 2017/04/22 21:31:54 by jye              ###   ########.fr        #
#                                                                              #
#******************************************************************************#

# Compiler

CC					=	gcc
CFLAG				=	-Wall -Wextra -Werror
LIB					=	-L libft -lft -L ft_printf -lftprintf
# Directories

SRC_PATH		=	src
OBJ_PATH		=	obj
INC_PATH		=	include

# Source files

SRC_FILE		=	color.c ctime.c free_.c get_arg.c get_opt.c				\
					init_cdir__.c init_file__.c								\
					main.c normal.c perm.c print_ell.c print_lsfiles.c		\
					read_.c recursive.c rsort_int.c rsort_ascii.c			\
					set_.c set_flag.c set_ls_args.c sort_.c sort_ascii.c	\
					sort_int.c utils.c set_timespec.c

# Object files

OBJ_FILE		=	$(addprefix $(OBJ_PATH)/, $(addsuffix .o, $(basename $(SRC_FILE))))

# Binary name

NAME			=	ft_ls

# Rules

all			: $(NAME)

.PHONY		: clean fclean re

clean		:
	make -C libft fclean
	make -C ft_printf fclean
	/bin/rm -rf $(OBJ_PATH)

fclean		: clean
	/bin/rm -rf $(NAME)
	/bin/rm -rf $(NAME).dSYM

re			: fclean all

$(NAME)		: $(OBJ_FILE) $(INC_PATH) lib
	$(CC) $(LIB) $(OBJ_FILE) -o $@

lib			:
	make -C libft
	make -C ft_printf

$(OBJ_PATH)/%.o	: $(SRC_PATH)/%.c
	@/bin/mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAG) -c -o $@ $< -I$(INC_PATH)
