# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/30 13:25:13 by ldedier           #+#    #+#              #
#    Created: 2018/12/04 15:20:42 by ldedier           #+#    #+#              #
#    Updated: 2018/12/06 16:56:32 by ldedier          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= corewar

CC      = gcc -g

PWD = $(shell pwd)

DEBUG ?= 0

SRCDIR   = srcs
OBJDIR   = objs
BINDIR   = .
INCLUDESDIR = includes
INSDIR = instructions
VISUDIR = visu

LIBFTDIR = ../libft
LIBFT_INCLUDEDIR = includes
LIBFT = $(LIBFTDIR)/libft.a

LIBOPDIR = ../libop
LIBOP_INCLUDEDIR = includes
LIBOP = $(LIBOPDIR)/libop.a

OK_COLOR = \x1b[32;01m
EOC = \033[0m


SRCS_NO_PREFIX =		arena.c error.c flags.c main.c parse.c read.c \
						tmp.c utils.c op.c play.c env.c \
						client.c bonus_flags.c net_tools.c test.c \
						display.c display_player.c display_resize.c\
						display_turn.c local_players.c

INS_NO_PREFIX =			get_val.c load_val.c\
						live.c ld.c st.c add.c sub.c and.c or.c xor.c zjmp.c \
						ldi.c sti.c fork.c lld.c lldi.c lfork.c aff.c inst_utils.c

VISU_NO_PREFIX =		init_sdl.c visu.c events.c framerate.c render.c \
						render_mem.c render_players.c ft_colors.c\
						render_online.c drag.c drop.c\
						cursor.c


INCLUDES_NO_PREFIX =	vm.h visu.h client.h

SOURCES = $(addprefix $(SRCDIR)/, $(SRCS_NO_PREFIX)) \
		$(addprefix $(SRCDIR)/$(INSDIR)/, $(INS_NO_PREFIX))\
		$(addprefix $(SRCDIR)/$(VISUDIR)/, $(VISU_NO_PREFIX))

OBJECTS =	$(addprefix $(OBJDIR)/, $(SRCS_NO_PREFIX:%.c=%.o)) \
		$(addprefix $(OBJDIR)/$(INSDIR)/, $(INS_NO_PREFIX:%.c=%.o)) \
		$(addprefix $(OBJDIR)/$(VISUDIR)/, $(VISU_NO_PREFIX:%.c=%.o))

INCLUDES = $(addprefix $(INCLUDESDIR)/, $(INCLUDES_NO_PREFIX))

INC = -I $(INCLUDESDIR) -I $(LIBFTDIR)/$(LIBFT_INCLUDEDIR)\
	  -I $(LIBOPDIR)/$(LIBOP_INCLUDEDIR) \
	-I $(FRAMEWORKSDIR)/SDL2

FRAMEWORKSDIR = $(PWD)/../frameworks

LFLAGS = -L $(LIBFTDIR) -lft -L $(LIBOPDIR) -lop\
		 -Wl,-rpath $(FRAMEWORKSDIR)

CFLAGS = -DPATH=\"$(PWD)\" -Wall -Wextra -Werror\
		 -Wno-missing-field-initializers $(INC)\

ifeq ($(DEBUG), 1)
	LFLAGS += -fsanitize=address
	CFLAGS += -DDEBUG
	CC += -g3
endif

SDL2_FRAMEWORKS =	-framework SDL2 -framework SDL2_image \
					-framework SDL2_mixer -framework SDL2_ttf\
					-framework SDL2_net
opti:
	@make all -j

optilibcomp:
	@make libcomp -j

libcomp:
	@make $(BINDIR)/$(NAME)

all:
	@make -C $(LIBFTDIR) all
	@make -C $(LIBOPDIR) all
	@make $(BINDIR)/$(NAME)

debug:
	@make opti DEBUG=1

$(LIBFT):
	@make -C $(LIBFTDIR) all
	#@$(CC) -o $@ $^ -F $(FRAMEWORKSDIR) $(CFLAGS) $(LFLAGS) #pour linux Emma | desolee!

$(BINDIR)/$(NAME): $(OBJECTS)  $(LIBFT) $(LIBOP)
	@$(CC) -o $@ $^ -F $(FRAMEWORKSDIR) $(SDL2_FRAMEWORKS) $(CFLAGS) $(LFLAGS)
	@echo "$(OK_COLOR)$(NAME) linked with success !$(EOC)"

$(OBJDIR)/%.o : $(SRCDIR)/%.c $(INCLUDES)
	@mkdir -p $(OBJDIR)
	@mkdir -p $(OBJDIR)/$(INSDIR)
	@mkdir -p $(OBJDIR)/$(VISUDIR)
#	@$(CC) -c $< -o $@ -F $(CFLAGS)
	@$(CC) -c $< -o $@ -F $(FRAMEWORKSDIR) $(CFLAGS)

$(OBJDIR)/$(INSDIR)/%.o : $(SRCDIR)/$(INSDIR)/%.c $(INCLUDES)
#	@$(CC) -c $< -o $@ -F $(CFLAGS)
	@$(CC) -c $< -o $@ -F $(FRAMEWORKSDIR) $(CFLAGS)

$(OBJDIR)/$(VISUDIR)/%.o : $(SRCDIR)/$(VISUDIR)/%.c $(INCLUDES)
	@$(CC) -c $< -o $@ -F $(FRAMEWORKSDIR) $(CFLAGS)

clean:
	@make clean -C $(LIBOPDIR)
	@rm -f $(OBJECTS)
	@rm -rf $(OBJDIR)

fclean: clean
	@make fclean -C $(LIBOPDIR)
	@rm -f $(BINDIR)/$(NAME)

re: fclean opti

.PHONY: all clean fclean re
