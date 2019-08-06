# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amerlon- <amerlon-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/21 20:01:04 by amerlon-          #+#    #+#              #
#    Updated: 2018/12/27 04:28:30 by amerlon-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol
FLAGS = -Wall -Werror -Wextra
SRCS = *.c
OBJS = *.o
INCLUDES = includes
LIBFT = libft.a

all: $(NAME)

$(OBJS):
	@gcc -c $(SRCS) $(FLAGS) -I$(INCLUDES)

$(NAME): $(OBJS)
	@gcc $(OBJS) -o $(NAME) $(LIBFT) -lmlx -framework OpenGL -framework AppKit

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re norm