# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/29 17:38:52 by ldedier           #+#    #+#              #
#    Updated: 2018/11/29 20:22:54 by ldedier          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

DEBUG ?= 0

LIBFTDIR		= libft
VMDIR			= vm_dir
ASMDIR			= asm_dir
DECOMPILERDIR	= decompiler_dir

VM_NAME			= corewar
ASM_NAME		= asm
DECOMPILER_NAME = decompiler

opti:
	@make all -j
all:
	@make -C $(LIBFTDIR) opti
	@make -C $(ASMDIR) optilibcomp
	@make -C $(VMDIR) optilibcomp
	@make -C $(DECOMPILERDIR) optilibcomp

debug:
	@make opti DEBUG=1

redebug: fclean debug

$(LIBFT):
	@make -C $(LIBFTDIR) opti
$(VMDIR):
	@make -C $(VMDIR) opti
$(ASMDIR):
	@make -C $(VMDIR) opti
$(DECOMPILERDIR):
	@make -C $(VMDIR) opti

clean:
	@make clean -C $(LIBFTDIR)
	@make clean -C $(ASMDIR)
	@make clean -C $(VMDIR)
	@make clean -C $(DECOMPILERDIR)

fclean: clean
	@make fclean -C $(LIBFTDIR)
	@make fclean -C $(ASMDIR)
	@make fclean -C $(VMDIR)
	@make fclean -C $(DECOMPILERDIR)
	@rm -f $(VM_NAME)
	@rm -f $(ASM_NAME)
	@rm -f $(DECOMPILER_NAME)

re: fclean opti

.PHONY: all clean fclean re
