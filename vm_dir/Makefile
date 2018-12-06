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

LIBFTDIR = ../libft
LIBFT_INCLUDEDIR = includes
LIBFT = $(LIBFTDIR)/libft.a

LIBOPDIR = ../libop
LIBOP_INCLUDEDIR = includes
LIBOP = $(LIBOPDIR)/libop.a

OK_COLOR = \x1b[32;01m
EOC = \033[0m

SRCS_NO_PREFIX =		arena.c error.c flags.c main.c parse.c read.c visu.c\
						tmp.c utils.c op.c play.c get_instruction.c \
						init_sdl.c client.c bonus_flags.c net_tools.c

INS_NO_PREFIX =			live.c ld.c st.c add.c sub.c and.c or.c xor.c zjmp.c \
						ldi.c sti.c fork.c lld.c lldi.c lfork.c aff.c

INCLUDES_NO_PREFIX =	vm.h visu.h client.h

SOURCES = $(addprefix $(SRCDIR)/, $(SRCS_NO_PREFIX)) \
		$(addprefix $(SRCDIR)/$(INSDIR)/, $(INS_NO_PREFIX))
OBJECTS =	$(addprefix $(OBJDIR)/, $(SRCS_NO_PREFIX:%.c=%.o))
OBJECTS +=	$(addprefix $(OBJDIR)/$(INSDIR)/, $(INS_NO_PREFIX:%.c=%.o))

INCLUDES = $(addprefix $(INCLUDESDIR)/, $(INCLUDES_NO_PREFIX))

INC = -I $(INCLUDESDIR) -I $(LIBFTDIR)/$(LIBFT_INCLUDEDIR)\
	  -I $(LIBOPDIR)/$(LIBOP_INCLUDEDIR)

LFLAGS = -L $(LIBFTDIR) -lft -L $(LIBOPDIR) -lop

CFLAGS = -DPATH="$(PWD)" -Wall -Wextra -Werror\
		 -Wno-missing-field-initializers $(INC)

ifeq ($(DEBUG), 1)
	LFLAGS += -fsanitize=address
	CFLAGS += -DDEBUG
	CC += -g3
endif

FRAMEWORKSDIR = ../frameworks

SDL2 = $(PWD)/$(FRAMEWORKSDIR)/SDL2.framework/Versions/A/SDL2
SDL2_image = $(PWD)/$(FRAMEWORKSDIR)/SDL2_image.framework/Versions/A/SDL2_image
SDL2_mixer = $(PWD)/$(FRAMEWORKSDIR)/SDL2_mixer.framework/Versions/A/SDL2_mixer
SDL2_ttf = $(PWD)/$(FRAMEWORKSDIR)/SDL2_ttf.framework/Versions/A/SDL2_ttf
SDL2_net = $(PWD)/$(FRAMEWORKSDIR)/SDL2_net.framework/Versions/A/SDL2_net

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

#	@$(CC) -o $@ $^ -F $(FRAMEWORKSDIR) $(CFLAGS) $(LFLAGS) #pour linux Emma | desolee!

$(BINDIR)/$(NAME): $(OBJECTS)  $(LIBFT)
	@$(CC) -o $@ $^ -F $(FRAMEWORKSDIR) $(SDL2_FRAMEWORKS) $(CFLAGS) $(LFLAGS)
	@echo "$(OK_COLOR)$(NAME) linked with success !$(EOC)"
	@install_name_tool -change @rpath/SDL2.framework/Versions/A/SDL2 $(SDL2) $(NAME)
	@install_name_tool -change @rpath/SDL2_image.framework/Versions/A/SDL2_image $(SDL2_image) $(NAME)
	@install_name_tool -change @rpath/SDL2_mixer.framework/Versions/A/SDL2_mixer $(SDL2_mixer) $(NAME)
	@install_name_tool -change @rpath/SDL2_ttf.framework/Versions/A/SDL2_ttf $(SDL2_ttf) $(NAME)
	@install_name_tool -change @rpath/SDL2_net.framework/Versions/A/SDL2_net $(SDL2_net) $(NAME)

$(OBJDIR)/%.o : $(SRCDIR)/%.c $(INCLUDES)
	@mkdir -p $(OBJDIR)
	@mkdir -p $(OBJDIR)/$(INSDIR)
	@$(CC) -c $< -o $@ -F $(FRAMEWORKSDIR) $(CFLAGS)

$(OBJDIR)/$(INSDIR)/%.o : $(SRCDIR)/$(INSDIR)/%.c $(INCLUDES)
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
