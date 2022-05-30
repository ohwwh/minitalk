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

LIBDIR=./libohw
LIBINCSDIR=./libohw/includes
CNTDIR=./client
SVRDIR=./server

.PHONY: all bonus clean fclean re

all : 
	make -C $(LIBDIR)
	make -C $(CNTDIR)
	make -C $(SVRDIR)

bonus : 
	make -C $(LIBDIR)
	make -C $(CNTDIR)
	make -C $(SVRDIR)

clean:
	make -C $(LIBDIR) clean
	make -C $(CNTDIR) clean
	make -C $(SVRDIR) clean

fclean: clean
	make -C $(LIBDIR) fclean
	make -C $(CNTDIR) fclean
	make -C $(SVRDIR) fclean

re: fclean all
