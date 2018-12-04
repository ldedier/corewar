/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   navigate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 15:37:35 by emuckens          #+#    #+#             */
/*   Updated: 2018/12/04 21:32:25 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int		is_valid_opcode(char hex)
{
	if (hex >= NB_INSTRUCTIONS)
		ft_printf("invalid opcode!\n");
	return (hex < NB_INSTRUCTIONS);
}

static int		needs_ocp(int op)
{
	return (op != LIVE && op != ZJMP && op != FORK && op != LFORK);
}


static int		is_valid_ocp(char hex, int opcode, t_arg **arg)
{
	int	type[3] = {1, 10, 11};
	int i = 0;
	int	t = 0;

	while (i < 4)
	{	
		t = -1;
		while (++t < 3)
		{
			if (hex & (type[t] << (i + i)))
			{
				hex ^= (type[t] << (i + i));
				(*arg)[i].nb_bytes = ft_pow(2, i);
			}
			else
				(*arg)[i].nb_bytes = 0;
		}
		++i;
	}
	if (needs_ocp(opcode) && hex)
	{
		ft_printf("invalid ocp!\n");
		return (0);
	}
	return (1);
}	

static int		store_argval(t_arg **arg, t_op *op, t_process *pr, t_arena *ar)
{
	int cursor;
	int	i;

	i = -1;
	cursor = pr->pc;
	while (++i < op->nb_params)
	{
		if (cursor + (*arg)[i].nb_bytes < MEM_SIZE)
		{
			if (!((*arg)[i].nb_bytes & op->arg_types[i]))
			{
				ft_printf("invalid file type!\n");
				return (0);
			}
			ft_memmove((void *)&(*arg)[i], (void *)(ar + cursor), (*arg)[i].nb_bytes);
			cursor += (*arg)[i].nb_bytes;
		}
		else // verifier si argument chevauche fin de l'arene
			;
	}
	return (1);
}

int				get_instruction(t_vm *vm, t_op tab[17], t_process *pr)
{
	char	hex;
	int		opcode;
	t_arg	arg[3];
	static int 	(*ins[NB_INSTRUCTIONS + 1])(t_vm *vm, t_process *proc,
			t_arg arg[3]) = {NULL, &ins_live, &ins_ld,
		&ins_st, &ins_add, &ins_sub, &ins_and, &ins_or, &ins_xor, &ins_zjmp,
		&ins_ldi, &ins_sti, &ins_fork, &ins_lld, &ins_lldi, &ins_lfork,
		&ins_aff};

	hex = *(char *)vm->arena;
	if (!(opcode = is_valid_opcode(hex)))
		return (0);
	if ((hex = *(char *)(vm->arena + 1)) && !is_valid_ocp(hex, opcode, (t_arg **)&arg))
		return (0);
	if (store_argval((t_arg **)&arg, &tab[opcode], pr, vm->arena))
	{
		ft_printf("valid opcode! = %d in index %d\n", opcode, pr->pc);
		ins[opcode](vm, pr, arg);
		pr->pc = (1 + needs_ocp(opcode) + arg[FIRST].nb_bytes
			+ arg[SECOND].nb_bytes + arg[THIRD].nb_bytes) % MEM_SIZE;
		return (opcode);
	}
	return (0);
}

