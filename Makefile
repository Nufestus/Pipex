# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aammisse <aammisse@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/27 01:39:09 by aammisse          #+#    #+#              #
#    Updated: 2025/02/04 16:36:40 by aammisse         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror

NAME = pipex
BNAME = pipex_bonus
SRCS = Mandatory/ft_split.c Mandatory/ft_strjoin.c Mandatory/pipex.c Mandatory/functions.c
BSRCS = Bonus/ft_split_bonus.c Bonus/pipex_bonus.c Bonus/GNL/get_next_line_bonus.c Bonus/GNL/get_next_line_utils_bonus.c \
		Bonus/heredoc_bonus.c Bonus/functions_bonus.c
OBJS = $(SRCS:.c=.o)
BOBJS = $(BSRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) Mandatory/pipex.h
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

bonus: $(BOBJS) Bonus/pipex_bonus.h Bonus/GNL/get_next_line_bonus.h
	$(CC) $(CFLAGS) $(BOBJS) -o $(BNAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS) $(BOBJS)

fclean: clean
	rm -rf $(NAME) $(BNAME)

re: fclean all