# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/26 12:37:33 by awerebea          #+#    #+#              #
#    Updated: 2020/10/27 22:33:22 by awerebea         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo_one
INCLUDES	= -I includes/
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
OFLAGS		= -O2
DBGFLAGS	= -g

override FLAGS ?= $(CFLAGS)

#------------------------------- minishell compiling ---------------------------
SRCDIR		= srcs/
OBJDIR		= objs/

FLSDIR_1	= ./
FLS_1		= $(addprefix $(FLSDIR_1), \
				init \
				main )
FLSDIR_2	= tools/
FLS_2		= $(addprefix $(FLSDIR_2), \
				ft_atoi \
				ft_isdigit \
				ft_putchar_fd \
				ft_putnbr_fd \
				ft_putstr_fd )

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

clean_all: clean libft_clean

fclean:	clean
	rm -f	$(NAME)

fclean_all: fclean libft_fclean

debug:
	make FLAGS="$(CFLAGS) $(DBGFLAGS)" all

run: all
	./$(NAME)

test: debug
	# valgrind --leak-check=full --show-leak-kinds=all -s ./$(NAME)
	./$(NAME)

re:	fclean all

.PHONY:	all \
	clean \
	clean_all \
	fclean \
	fclean_all \
	debug \
	run \
	run_debug \
	re
