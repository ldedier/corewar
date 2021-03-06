# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/21 13:40:59 by ldedier           #+#    #+#              #
#    Updated: 2019/03/15 01:41:35 by ldedier          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= asm

CC      = gcc

PWD = \"$(shell pwd)\"

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

SRCS_NO_PREFIX		=	main.c ft_init.c ft_parse_header.c\
					 	ft_log_errors.c ft_debug.c ft_free.c ft_encode.c\
						ft_parse_tools00.c\
						ft_init_parser.c ft_process_parse.c ft_parse_suite.c\
						ft_parse_label.c ft_log.c ft_process_parse_header.c\
						ft_process_parse_suite.c ft_parse_tools01.c ft_parse.c\
						ft_debug_suite.c ft_encode_suite.c ft_parse_tools03.c\
						ft_log_warnings.c ft_parse_tools02.c ft_log_header.c\


INCLUDES_NO_PREFIX	=	asm.h

OP_INCLUDES_NO_PREFIX = champion.h errors.h op.h player.h

SOURCES = $(addprefix $(SRCDIR)/, $(SRCS_NO_PREFIX))
OBJECTS = $(addprefix $(OBJDIR)/, $(SRCS_NO_PREFIX:%.c=%.o))
INCLUDES = $(addprefix $(INCLUDESDIR)/, $(INCLUDES_NO_PREFIX))
OP_INCLUDES = $(addprefix $(LIBOPDIR)/$(LIBOP_INCLUDEDIR)/, $(OP_INCLUDES_NO_PREFIX))
INC = -I $(INCLUDESDIR) -I $(LIBFTDIR)/$(LIBFT_INCLUDEDIR)\
	  -I $(LIBOPDIR)/$(LIBOP_INCLUDEDIR)

CFLAGS = -DPATH=$(PWD) -Wall -Wextra -Werror\
		 -Wno-missing-field-initializers $(INC)

LFLAGS = -L $(LIBFTDIR) -lft -L $(LIBOPDIR) -lop

ifeq ($(DEBUG), 1)
	LFLAGS += -fsanitize=address
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
	@make -C $(LIBOPDIR) opti
	@make $(BINDIR)/$(NAME)

debug:
	@make opti DEBUG=1

$(LIBFT):
	@make -C $(LIBFTDIR) opti
$(LIBOP):
	@make -C $(LIBOPDIR) opti

$(BINDIR)/$(NAME): $(OBJECTS) $(LIBFT) $(LIBOP)
	@$(CC) -o $@ $^ $(CFLAGS) $(LFLAGS)
	@echo "$(OK_COLOR)$(NAME) linked with success !$(EOC)"

$(OBJDIR)/%.o : $(SRCDIR)/%.c $(INCLUDES) $(OP_INCLUDES)
	@mkdir -p $(OBJDIR)
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	@make clean -C $(LIBOPDIR)
	@rm -f $(OBJECTS)
	@rm -rf $(OBJDIR)

fclean: clean
	@make fclean -C $(LIBOPDIR)
	@rm -f $(BINDIR)/$(NAME)

re: fclean opti

.PHONY: all clean fclean re
