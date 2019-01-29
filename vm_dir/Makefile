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

CC      = gcc -g3

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


SRCS_NO_PREFIX =		arena.c error.c flags.c main.c parse.c \
						tmp.c utils.c op.c play.c env.c \
						bonus_flags.c net_tools.c \
						test.c display.c display_player.c display_resize.c \
						display_turn.c local_players.c init_vm.c \
						init_players.c

INS_NO_PREFIX =			get_val.c load_val.c\
						live.c ld.c st.c add.c sub.c and.c or.c xor.c zjmp.c \
						ldi.c sti.c fork.c lld.c lldi.c lfork.c aff.c

VISU_NO_PREFIX =		init_sdl.c visu.c events.c framerate.c render.c \
						render_mem.c render_players.c ft_colors.c\
						render_online.c drag.c drop.c\
						cursor.c scrollbar.c scrollbar_tools.c\
						render_scrollbar.c render_view.c render_line.c\
						render_phase.c scroll_scrollbar.c init_scrollbar.c\
						populate_drag_container.c is_on_scrollbar.c\
						drop_actions.c is_droppable.c is_on_draggable_server.c\
						load_tools.c atlas.c init_center.c init_textures.c\
						init_slots.c init_buttons.c visu_tools.c\
						render_buttons.c buttons_actions.c init_all.c\
						is_on_buttons.c mouse.c process.c upload.c\
						client.c query_player.c query_player_bin.c\
						render_notification.c render_play.c render_entries_1.c\
						render_entries_2.c render_player_entries.c\
						render_live_breakdown.c render_live_breakdown_hp.c\
						render_play_footer.c sort.c free_all_visu.c\
						client_events.c client_slot.c client_slot_add.c\
						download.c client_status.c copy_str_to_surface.c\
						render_inner_player.c render_player_tools.c\
						render_players_2.c render_player_entries_funcs.c\
						buttons_actions_client.c buttons_actions_2.c\
						free_all_visu_2.c init_center_play.c init_center_2.c\
						update_scrollbar.c init_textures_hp.c\
						render_live_breakdown_hp_tools.c render_online_top.c\
						render_online_2.c render_live.c render_fade.c\
						render_activity.c client_get_new_cores.c render_alts.c


INCLUDES_NO_PREFIX =	vm.h visu.h client.h

#SOURCES = $(addprefix $(SRCDIR)/, $(SRCS_NO_PREFIX)) \
#		$(addprefix $(SRCDIR)/$(INSDIR)/, $(INS_NO_PREFIX)) \
#		$(addprefix $(SRCDIR)/$(VISUDIR)/, $(VISU_NO_PREFIX))

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
					-framework SDL2_mixer -framework SDL2_ttf \
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

$(BINDIR)/$(NAME): $(OBJECTS)  $(LIBFT) $(LIBOP)
	@$(CC) -o $@ $^ -F $(FRAMEWORKSDIR) $(SDL2_FRAMEWORKS) $(CFLAGS) $(LFLAGS)
	@echo "$(OK_COLOR)$(NAME) linked with success !$(EOC)"

$(OBJDIR)/%.o : $(SRCDIR)/%.c $(INCLUDES) $(LIBOP)
	@mkdir -p $(OBJDIR)
	@mkdir -p $(OBJDIR)/$(INSDIR)
	@mkdir -p $(OBJDIR)/$(VISUDIR)
	$(CC) -c $< -o $@ -F $(FRAMEWORKSDIR) $(CFLAGS)

$(OBJDIR)/$(INSDIR)/%.o : $(SRCDIR)/$(INSDIR)/%.c $(INCLUDES)
	$(CC) -c $< -o $@ -F $(FRAMEWORKSDIR) $(CFLAGS)

$(OBJDIR)/$(VISUDIR)/%.o : $(SRCDIR)/$(VISUDIR)/%.c $(INCLUDES)
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
