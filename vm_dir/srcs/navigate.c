/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   navigate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 15:37:35 by emuckens          #+#    #+#             */
/*   Updated: 2018/12/06 16:40:38 by emuckens         ###   ########.fr       */
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


static int		is_valid_ocp(char hex, t_instruction *ins)
{
	int	type[3] = {1, 10, 11};
	int i = -1;
	int	t = 0;

	while (++i < 4 && (t = -1))
		while (++t < 3)
		{
			if (hex & (type[t] << (i + i)))
			{
				hex ^= (type[t] << (i + i));
				ins->params[i].nb_bytes = ft_pow(2, i);
			}
			else
				ins->params[i].nb_bytes = 0;
		}
	return (!(needs_ocp(ins->op.opcode) && hex));
}	

static int			arg_reg(char *arena, t_parameter *arg, int i)
{

	if (arg->nb_bytes & T_REG)
			arg->value = *(char *)(arena + i);
	else if (i + arg->nb_bytes < MEM_SIZE)
		ft_memmove((void *)&arg->value, (void *)(arena + i), arg->nb_bytes);
	else
	{
		ft_memmove((void *)&arg->value, (void *)(arena + i), MEM_SIZE - i);
		ft_memmove((void *)&arg->value, (void *)(arena + i),
				(i + arg->nb_bytes) % MEM_SIZE);
	}
	return (arg->nb_bytes);
}

static int		arg_mod(char *arena, t_parameter *arg, int i)
{
	ft_memmove((void *)&arg->value, (void *)(arena + i), IND_SIZE);
	return (IND_SIZE);
}

static int		arg_uni(char *arena, t_parameter *arg, int i)
{
	ft_memmove((void *)&arg->value, (void *)(arena + i), 1);
	return (1);
}

static int		store_arg(char *arena, t_instruction *ins, int i, int ocp)
{
	int	arg;
	int	start;
	static int (*fstore[NB_INSTRUCTIONS])(char *ar, t_parameter *arg, int c) =
	{&arg_mod, &arg_reg, &arg_reg, &arg_reg, &arg_reg, &arg_reg, &arg_reg,
	&arg_reg, &arg_mod, &arg_reg, &arg_reg, &arg_mod, &arg_reg, &arg_reg,
	&arg_mod, &arg_uni};

	arg = -1;
	start = i;
	while (++arg < ins->op.nb_params)
	{
		ft_printf("ocp = %d ins op arg type = %d\n", ocp, ins->op.arg_types[i]);
		ocp = ocp & (11 << i);
		ocp = (ocp >> (i + i));
		if (!(ocp & ins->op.arg_types[i])
			|| ((ocp & T_REG && *(arena + i) >= REG_NUMBER)))
		{
			ft_printf("invalid file type!\n");
			return (0);
		}
		i += fstore[(int)ins->op.opcode](arena, &ins->params[arg], i);
	}
	return (i - start);
}

int				get_instruction(char *arena, t_op *tab, int i, t_instruction *ins)
{
	char	hex;
	int		arglen;
	t_parameter	*arg;
	int		ret;


	hex = *(arena + (i >= MEM_SIZE ? 0 : i));
	if (!(ret = is_valid_opcode(hex)))
		return (0);
	else
		ft_memmove((void *)&ins->op, (void *)&tab[ret], sizeof(t_op));
	hex = *(arena + ((unsigned int)(i + 1) >= MEM_SIZE ? 1 : i + 1));
	if (!(ins->ocp = is_valid_ocp(hex, ins)))
		return (0);
	if (!(ins->params->nb_bytes = store_arg(arena, ins, i, ins->ocp)))
		return (0);
	ft_printf("valid opcode! = %d in index %d\n", ins->op.opcode, i);
	arg = ins->params;
	arglen = arg[0].nb_bytes + arg[1].nb_bytes + arg[2].nb_bytes;
	return (1 + needs_ocp(ins->op.opcode) + arglen);
}

int			launch_instruction(t_vm *vm, t_process *proc, t_op *tab)
{
	t_instruction	ins;
	int				ret;
	static int 	(*f_ins[NB_INSTRUCTIONS + 1])(t_vm *vm, t_process *proc,
			t_parameter arg[3]) = {NULL, &ins_live, &ins_ld,
		&ins_st, &ins_add, &ins_sub, &ins_and, &ins_or, &ins_xor, &ins_zjmp,
		&ins_ldi, &ins_sti, &ins_fork, &ins_lld, &ins_lldi, &ins_lfork,
		&ins_aff};

	ft_printf("launch instruction | proc cycle = %d\n", proc->cycle);
	if (--proc->cycle)
		return (1);
	ft_bzero((void *)&ins, sizeof(ins));
	if ((ret = get_instruction((char *)vm->arena, (t_op *)tab, proc->pc, &ins)))
	{
		f_ins[(int)ins.op.opcode](vm, proc, ins.params);
		proc->pc = (proc->pc + ret) & MEM_SIZE;
		return (tab[(int)ins.op.opcode].nb_cycles);
	}
	proc->pc = (proc->pc == MEM_SIZE - 1 ? 0 : proc->pc + 1);
	return (1);
}
