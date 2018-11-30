# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/21 13:40:59 by ldedier           #+#    #+#              #
#    Updated: 2018/11/30 13:35:09 by ldedier          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libop.a
CC      = gcc

PWD = \"$(shell pwd)\"

DEBUG ?= 0

BINDIR		= .
SRCDIR		= srcs
OBJDIR		= objs
INCLUDESDIR = includes

OK_COLOR = \x1b[32;01m
EOC = \033[0m

SRCS_NO_PREFIX = op.c

INCLUDES_NO_PREFIX = op.h

SOURCES = $(addprefix $(SRCDIR)/, $(SRCS_NO_PREFIX))
OBJECTS = $(addprefix $(OBJDIR)/, $(SRCS_NO_PREFIX:%.c=%.o))
INCLUDES = $(addprefix $(INCLUDESDIR)/, $(INCLUDES_NO_PREFIX))

INC = -I $(INCLUDESDIR)

CFLAGS = -DPATH=$(PWD) -Wall -Wextra -Werror\
		 -Wno-missing-field-initializers $(INC)

ifeq ($(DEBUG), 1)
	CFLAGS += -DDEBUG 
	CC += -g3
endif

opti:
	@make all -j

all:
	@make $(BINDIR)/$(NAME)

$(OBJDIR)/%.o : $(SRCDIR)/%.c $(INCLUDES)
	@mkdir -p $(OBJDIR)
	$(CC) -c $< -o $@ $(CFLAGS)

$(BINDIR)/$(NAME): $(OBJECTS)
	@ar rc $@ $^
	@ranlib $(NAME)
	@echo "$(OK_COLOR)$(NAME) linked with success !$(EOC)"
clean:
	@rm -f $(OBJECTS)
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -f $(BINDIR)/$(NAME)

re: fclean all

.PHONY: all clean fclean re
