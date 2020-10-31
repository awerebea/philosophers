# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/26 12:37:33 by awerebea          #+#    #+#              #
#    Updated: 2020/10/31 21:19:22 by awerebea         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo_one
INCLUDES	= -I includes/
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -pthread
OFLAGS		= -O2
DBGFLAGS	= -g

override FLAGS ?= $(CFLAGS)

#------------------------------- philo_one compiling ---------------------------
SRCDIR		= src/
OBJDIR		= obj/

FLSDIR_1	= ./
FLS_1		= $(addprefix $(FLSDIR_1), \
				main \
				simulation \
				threads )
FLSDIR_2	= tools/
FLS_2		= $(addprefix $(FLSDIR_2), \
				f_sleep \
				ft_atoi \
				ft_isdigit \
				ft_putchar_fd \
				ft_putnbr_fd \
				ft_putstr_fd \
				get_time_in_ms )

SRC	= $(FLS_1) $(FLS_2)

OBJ	= $(addprefix $(OBJDIR), $(SRC:=.o))
DFLS	= $(SRC:=.d)

all:		$(NAME)

$(NAME):	$(OBJ)
	@echo '---------- Making philo_one ----------'
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
	./$(NAME) 20 200 75 75

test: debug
	./$(NAME) 20 200 75 75

test_valgrind: debug
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME) 50 200 50 50 8

re:	fclean all

.PHONY:	all \
	clean \
	debug \
	fclean \
	re \
	run \
	test \
	test_valgrind
