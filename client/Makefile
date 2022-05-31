# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ohw <ohw@student.42seoul.kr>               +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/23 02:36:10 by ohw               #+#    #+#              #
#    Updated: 2022/04/28 12:44:39 by hoh              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME=client
NAME_BONUS=client_bonus
LIBDIR=../libohw
LIBINCSDIR=../libohw/includes
SRCSDIR=./
INCSDIR=../
SRCSBNSDIR=./
SRCS_NAME= client.c
SRCS=$(addprefix $(SRCSDIR), $(SRCS_NAME))

BONUS_NAME=${SRCS_NAME:.c=_bonus.c}

BONUS=$(addprefix $(SRCSBNSDIR), $(BONUS_NAME))

OBJS=${SRCS:.c=.o}

OBJSBNS=${BONUS:.c=.o}

.PHONY: all bonus clean fclean re

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INCSDIR)

all : $(NAME)

bonus : $(NAME_BONUS)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L$(LIBDIR) -I$(INCSDIR) -lohw

$(NAME_BONUS) : $(OBJSBNS)
	$(CC) $(CFLAGS) -o $(NAME_BONUS) $(OBJSBNS) -L$(LIBDIR) -I$(INCSDIR) -lohw

clean:
	rm -f $(OBJS) $(OBJSBNS)

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)

re: fclean all
