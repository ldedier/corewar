# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/29 17:38:52 by ldedier           #+#    #+#              #
#    Updated: 2019/03/04 15:06:56 by emuckens         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

DEBUG ?= 0

LIBFTDIR		= libft
LIBOPDIR		= libop
VMDIR			= vm_dir
ASMDIR			= asm_dir
DECOMPILERDIR	= decompiler_dir
SERVERDIR		= server_dir

VM_NAME			= corewar
ASM_NAME		= asm
DECOMPILER_NAME = decompiler
SERVER_NAME		= scorewar

opti:
	@make all

all:
	@make -C $(LIBFTDIR) opti
	@make -C $(LIBOPDIR) optilibcomp
	@make -C $(ASMDIR) optilibcomp
	@make -C $(VMDIR) optilibcomp
	@make -C $(DECOMPILERDIR) optilibcomp
	@make -C $(SERVERDIR) libcomp
	@cp $(ASMDIR)/$(ASM_NAME) .
	@cp $(VMDIR)/$(VM_NAME) .
	@cp $(DECOMPILERDIR)/$(DECOMPILER_NAME) .
	@cp $(SERVERDIR)/$(SERVER_NAME) .

debug:
	@make opti DEBUG=1

redebug: fclean debug

clean:
	@make clean -C $(LIBOPDIR)
	@make clean -C $(LIBFTDIR)
	@make clean -C $(ASMDIR)
	@make clean -C $(VMDIR)
	@make clean -C $(DECOMPILERDIR)
	@make clean -C $(SERVERDIR)

fclean: clean
	@make fclean -C $(LIBOPDIR)
	@make fclean -C $(LIBFTDIR)
	@make fclean -C $(ASMDIR)
	@make fclean -C $(VMDIR)
	@make fclean -C $(DECOMPILERDIR)
	@make fclean -C $(SERVERDIR)

	@rm -f $(VM_NAME)
	@rm -f $(ASM_NAME)
	@rm -f $(DECOMPILER_NAME)
	@rm -f $(SERVER_NAME)

re: fclean opti

.PHONY: all clean fclean re
