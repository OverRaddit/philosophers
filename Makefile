# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gshim <gshim@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/22 17:48:50 by gshim             #+#    #+#              #
#    Updated: 2022/04/19 13:41:48 by gshim            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# =============================================================================
# Color Variables
# =============================================================================

BLACK		= 	"\033[0;30m"
GRAY		= 	"\033[1;30m"
RED			=	"\033[0;31m"
GREEN		=	"\033[0;32m"
YELLOW		=	"\033[1;33m"
PURPLE		=	"\033[0;35m"
CYAN		=	"\033[0;36m"
WHITE		=	"\033[1;37m"
EOC			=	"\033[0;0m"
LINE_CLEAR	=	"\x1b[1A\x1b[M"

# =============================================================================
# Command Variables
# =============================================================================
CC = gcc
CFLAGS =
#CFLAGS = -Wall -Wextra -Werror
#CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

NAME = philosophers

SRCS_DIR = ./src
SRCS =  src/personal_info.c src/philosophers.c src/thread.c \
		src/utils.c src/utils2.c src/monitor.c src/error.c

OBJS = $(SRCS:.c=.o)

SHELL	= /bin/bash
sp		= /-\|/
idx		= 0

#======================= 외부라이브러리 모음 ==========================
# LIB_NAME = ft
# LIB_DIR = ./include/libft
# LIB = $(addprefix $(LIB_DIR)/, libft.a)

#=================================================================

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) -lpthread $^ -o $@

$(SRCS_DIR)/%.o : $(SRCS_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@
#	$(eval idx = $(shell expr $(idx) + 1))
#	$(eval t_idx = $(shell expr $(idx) % 4 + 1))
#	$(eval chr = $(shell echo $(sp) | cut -c $(t_idx)))
#	@if [ $(idx) = 1 ]; then\
#		echo -n "☕️ ☕️ PHILOSOPHERS Loading ...\n";\
#	fi
#	@printf "\b$(chr)"
#	@$(CC) $(CFLAGS) $< -o $@
#	@$(CC) $(CFLAGS) -c $< -o $@
#-lpthread 랑 -c를 같이쓰면 오류
all : $(NAME)

clean :
	rm -rf $(OBJS)

fclean :
	rm -rf $(NAME) $(OBJS)

re : fclean all

.PHONY : all clean fclean re
