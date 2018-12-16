# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/21 13:40:59 by ldedier           #+#    #+#              #
#    Updated: 2018/12/12 20:42:20 by emuckens         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libop.a
CC      = gcc -g

PWD = \"$(shell pwd)\"

DEBUG ?= 0

BINDIR		= .
SRCDIR		= srcs
OBJDIR		= objs
INCLUDESDIR = includes

LIBFTDIR = ../libft
LIBFT_INCLUDEDIR = includes
LIBFT = $(LIBFTDIR)/libft.a

OK_COLOR = \x1b[32;01m
EOC = \033[0m

SRCS_NO_PREFIX =	op.c ft_is_of_extension.c ft_switch_extension.c\
					ft_encode_instructions.c ft_read_player.c ft_parse_player.c\
					player.c get_instruction.c color.c

INCLUDES_NO_PREFIX = op.h champion.h player.h network.h color.h errors.h

SOURCES = $(addprefix $(SRCDIR)/, $(SRCS_NO_PREFIX))
OBJECTS = $(addprefix $(OBJDIR)/, $(SRCS_NO_PREFIX:%.c=%.o))
INCLUDES = $(addprefix $(INCLUDESDIR)/, $(INCLUDES_NO_PREFIX))

INC = -I $(INCLUDESDIR) -I $(LIBFTDIR)/$(LIBFT_INCLUDEDIR)

CFLAGS = -DPATH=$(PWD) -Wall -Wextra -Werror\
		 -Wno-missing-field-initializers $(INC)


ifeq ($(DEBUG), 1)
	CFLAGS += -DDEBUG
	CC += -g3
endif

opti:
	@make all -j

optilibcomp:
	@make libcomp -j

libcomp:
	@make $(BINDIR)/$(NAME)

all:
	@make -C $(LIBFTDIR)
	@make $(BINDIR)/$(NAME)

$(LIBFT):
	make -C $(LIBFTDIR) opti

$(OBJDIR)/%.o : $(SRCDIR)/%.c $(INCLUDES)
	@mkdir -p $(OBJDIR)
	$(CC) -c $< -o $@ $(CFLAGS)

$(BINDIR)/$(NAME): $(OBJECTS)
	@ar rc $@ $^
	@ranlib $(NAME)
	@echo "$(OK_COLOR)$(NAME) linked with success !$(EOC)"
clean:
	@make -C $(LIBFTDIR) clean
	@rm -f $(OBJECTS)
	@rm -rf $(OBJDIR)

fclean: clean
	@make -C $(LIBFTDIR) fclean
	@rm -f $(BINDIR)/$(NAME)

re: fclean all

.PHONY: all clean fclean re
