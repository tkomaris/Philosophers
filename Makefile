# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tkomaris <tkomaris@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/30 20:13:24 by tkomaris          #+#    #+#              #
#    Updated: 2022/03/30 22:11:32 by tkomaris         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo

SRCS = src/philo.c \
	   src/threads.c \
	   src/messages.c \
	   src/utils.c \

CFLAGS = -Wall -Wextra -Werror -pthread

CC = gcc

INC = inc/

HEADER = $(INC)philo.h

OBJ = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ) 
	 $(CC) $(CFLAGS) -o $@ $(OBJ)
	@echo "\nCompilation done!"
	@echo "\nInput: ./philo [num of philos] [time to die] [time to eat] [time to sleep] [num of times each philo must eat]"
	@echo "\nP.S. The last argument is optional"


%.o: %.c $(HEADER)
	$(CC) -c $(CFLAGS) -I $(INC) $< -o $@

norme :
	norminette src/

clean :
	$(RM) $(OBJ)
	@echo "Cleaning"
	
fclean : clean
	$(RM) $(NAME)
	@echo "Cleaning all"

re : fclean all

.PHONY : all norme clean fclean re
