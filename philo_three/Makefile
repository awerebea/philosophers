# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/30 16:58:34 by awerebea          #+#    #+#              #
#    Updated: 2020/11/01 12:41:54 by awerebea         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo_three
INCLUDES	= -I includes/
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -pthread
OFLAGS		= -O2
DBGFLAGS	= -g

override FLAGS ?= $(CFLAGS)

#------------------------------ philo_three compiling --------------------------
SRCDIR		= src/
OBJDIR		= obj/

FLSDIR_1	= ./
FLS_1		= $(addprefix $(FLSDIR_1), \
				main \
				processes \
				simulation )
FLSDIR_2	= tools/
FLS_2		= $(addprefix $(FLSDIR_2), \
				f_sleep \
				ft_atoi \
				ft_isdigit \
				ft_itoa \
				ft_putchar_fd \
				ft_putnbr_fd \
				ft_putstr_fd \
				ft_strncmp \
				get_time_in_ms )

SRC	= $(FLS_1) $(FLS_2)

OBJ	= $(addprefix $(OBJDIR), $(SRC:=.o))
DFLS	= $(SRC:=.d)

all:		$(NAME)

$(NAME):	$(OBJ)
	@echo '--------- Making philo_three ---------'
	$(CC)		$(FLAGS) $(OBJ) $(INCLUDES) -o $(NAME)
	@echo '------------- All done! --------------'

$(OBJ):		$(OBJDIR)%.o: $(SRCDIR)%.c
	mkdir -p	$(OBJDIR) $(addprefix $(OBJDIR), $(FLSDIR_1) $(FLSDIR_2))
	$(CC)		$(FLAGS) $(INCLUDES) -c $< -o $@ -MMD

include $(wildcard $(addprefix $(OBJDIR), $(DFLS)))

clean:
	rm -rf	$(OBJDIR)

fclean:	clean
	rm -f	$(NAME)

debug:
	make FLAGS="$(CFLAGS) $(DBGFLAGS)" all

run: all
	./$(NAME) 5 800 200 200

test: debug
	./$(NAME) 5 800 200 200

test_valgrind: debug
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME) 5 800 200 200 7

re:	fclean all

.PHONY:	all \
	clean \
	debug \
	fclean \
	re \
	run \
	test \
	test_valgrind
