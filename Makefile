# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/23 13:20:28 by smakni            #+#    #+#              #
#    Updated: 2019/03/07 15:28:04 by vrenaudi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	lem-in

CC			=	gcc

CFLAGS		+=	-Wall -Werror -Wextra -g3

CPPFLAGS	=	-I include -I libft/include

HEADER		=	./include/lemin.h
				
SRC_PATH	=	src

OBJ_PATH	=	obj

LDFLAGS		=	-L libft

LDLIBS		=	-lft

SRC_NAME	=	main.c \
				print_data.c \
				fill.c \
				read_data.c \
				handle_memory.c \
				create_rooms.c \
				fill_combinations.c \
				dispatch_ants.c \
				move_ants.c \
				calculate_line.c \
				bfs.c \
				fifo.c \
				bfs_second.c \
				fifo_second.c \
				algo.c \
				edmonds_karp.c \
				init_algo.c \
				free_memory.c \
				analyze_node_edge.c \
				options.c

OBJ_NAME	=	$(SRC_NAME:.c=.o)

SRC 		= 	$(addprefix $(SRC_PATH)/,$(SRC_NAME))

OBJ 		= 	$(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
		make -C libft
		$(CC) $(CFLAGS) -o $@ $(OBJ) $(LDFLAGS) $(LDLIBS)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(HEADER)
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

sanitize: 
		make -C libft
		$(CC) -fsanitize=address -g3  -o lem-in $(OBJ) $(LDFLAGS) $(LDLIBS)

resanitize: fclean $(OBJ) 
		make -C libft
		$(CC) -fsanitize=address -g3  -o lem-in $(OBJ) $(LDFLAGS) $(LDLIBS)

clean:
	rm -fv $(OBJ)
	rmdir $(OBJ_PATH) 2> /dev/null || true
	make clean -C libft

fclean: clean
	rm -fv $(NAME)
	make fclean -C libft

re:
	make fclean
	make

.PHONY: all, clean, fclean, re

norme_src:
	norminette src/*.[ch]
	norminette ./include

norme_lib:
	norminette ./libft/*/*.[ch]
	norminette ./libft/include
