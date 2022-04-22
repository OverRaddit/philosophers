# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gshim <gshim@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/22 17:48:50 by gshim             #+#    #+#              #
#    Updated: 2022/04/22 21:11:27 by gshim            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# =============================================================================
# Color Variables
# =============================================================================
BLACK		=	"\033[0;30m"
GRAY		=	"\033[1;30m"
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
CC			=	gcc
CFLAGS		=
#CFLAGS		=	-Wall -Wextra -Werror
CDEBUG		=	-g -fsanitize=address
CFLAGS		=	-g

# =============================================================================
# File Variables
# =============================================================================
NAME		=	philo_bonus
SRCS_DIR	=	./src/
SRC_LIST	=	init.c							\
				valid.c							\
				philosophers.c					\
				thread.c 						\
				monitor.c						\
				utils.c							\
				utils2.c						\
				error.c							\
				semaphore.c
SRCS		=	$(addprefix $(SRCS_DIR), $(SRC_LIST))
OBJS		=	$(SRCS:.c=.o)
# =============================================================================
# Target Generating
# =============================================================================
$(NAME)			:	$(OBJS)
	@echo $(GREEN) "Source files are compiled!\n" $(EOC)
	@echo $(WHITE) "Building $(NAME) for" $(YELLOW) "Mandatory" $(WHITE) "..." $(EOC)
	@$(CC) $(CFLAGS) -lpthread $^ -o $@
	@echo $(GREEN) "$(NAME) is created!\n" $(EOC)

#$(SRCS_DIR)/%.o	:	$(SRCS_DIR)/%.c
%.o				:	%.c
				@echo $(YELLOW) "Compiling...\t" $< $(EOC) $(LINE_CLEAR)
				@$(CC) $(CFLAGS) -o $@ -c $<
# =============================================================================
# Rules
# =============================================================================
all			: $(NAME)

clean		:
				@echo $(YELLOW) "Cleaning object files..." $(EOC)
				@rm -rf $(OBJS)
				@echo $(RED) "Object files are cleaned! 🧹 🧹\n" $(EOC)

fclean		:
				@echo $(YELLOW) "Removing $(NAME)..." $(EOC)
				@rm -rf $(NAME) $(OBJS)
				@echo $(RED) "$(NAME) is removed! 🗑 🗑\n" $(EOC)

re			: fclean all

.PHONY		: all clean fclean re
