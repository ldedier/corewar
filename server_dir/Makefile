# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/04 15:20:42 by ldedier           #+#    #+#              #
#    Updated: 2018/12/11 15:00:40 by ldedier          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= scorewar

CC      = gcc

PWD = $(shell pwd)

DEBUG ?= 0

SRCDIR   = srcs
OBJDIR   = objs
BINDIR   = .
INCLUDESDIR = includes

LIBFTDIR = ../libft
LIBFT_INCLUDEDIR = includes
LIBFT = $(LIBFTDIR)/libft.a

LIBOPDIR = ../libop
LIBOP_INCLUDEDIR = includes
LIBOP = $(LIBOPDIR)/libop.a

OK_COLOR = \x1b[32;01m
EOC = \033[0m

SRCS_NO_PREFIX =	main.c ft_process.c ft_fill_all.c tools.c ft_init_db.c ft_init.c ft_send_others.c

INCLUDES_NO_PREFIX = #server.h

SOURCES = $(addprefix $(SRCDIR)/, $(SRCS_NO_PREFIX))
OBJECTS = $(addprefix $(OBJDIR)/, $(SRCS_NO_PREFIX:%.c=%.o))
INCLUDES = $(addprefix $(INCLUDESDIR)/, $(INCLUDES_NO_PREFIX))

INC = -I $(INCLUDESDIR) -I $(LIBFTDIR)/$(LIBFT_INCLUDEDIR)\
	  -I $(LIBOPDIR)/$(LIBOP_INCLUDEDIR)

FRAMEWORKSDIR = $(PWD)/../frameworks

LFLAGS =	-L $(LIBFTDIR) -lft -L $(LIBOPDIR) -lop\
			-Wl,-rpath $(FRAMEWORKSDIR)

CFLAGS = -DPATH=\"$(PWD)\" -Wall -Wextra -Werror\
		 -Wno-missing-field-initializers $(INC)

ifeq ($(DEBUG), 1)
	LFLAGS += -fsanitize=address
	CFLAGS += -DDEBUG
	CC += -g3
endif


SDL2 = $(PWD)/$(FRAMEWORKSDIR)/SDL2.framework/Versions/A/SDL2
SDL2_net = $(PWD)/$(FRAMEWORKSDIR)/SDL2_net.framework/Versions/A/SDL2_net
SDL2_FRAMEWORKS =	-framework SDL2 -framework SDL2_net

opti:
	@make all -j
all:
	@make -C $(LIBFTDIR) all
	@make -C $(LIBOPDIR) all
	@make $(BINDIR)/$(NAME)

optilibcomp:
	@make libcomp -j

libcomp:
	@make $(BINDIR)/$(NAME)

debug:
	@make opti DEBUG=1

$(LIBFT):
	@make -C $(LIBFTDIR) all

$(BINDIR)/$(NAME): $(OBJECTS) $(LIBFT) $(LIBOP)
	@$(CC) -o $@ $^ -F $(FRAMEWORKSDIR) $(SDL2_FRAMEWORKS) $(CFLAGS) $(LFLAGS)
	@echo "$(OK_COLOR)$(NAME) linked with success !$(EOC)"

$(OBJDIR)/%.o : $(SRCDIR)/%.c $(INCLUDES)
	@mkdir -p $(OBJDIR)
	$(CC) -c $< -o $@ -F $(FRAMEWORKSDIR) $(CFLAGS)

clean:
	@make clean -C $(LIBOPDIR)
	@rm -f $(OBJECTS)
	@rm -rf $(OBJDIR)

fclean: clean
	@make fclean -C $(LIBOPDIR)
	@rm -f $(BINDIR)/$(NAME)

re: fclean opti

.PHONY: all clean fclean re
