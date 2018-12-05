/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   navigate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 15:37:35 by emuckens          #+#    #+#             */
/*   Updated: 2018/12/05 22:53:06 by emuckens         ###   ########.fr       */
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
		ocp = ocp && (11 << i);
		ocp = (ocp >> (i + i);
		if (!(ocp & ins->op.arg_types[i]))
			|| ((ocp & T_REG && *(arena + i) >= REG_NUMBER)))
		{
			ft_printf("invalid file type!\n");
			return (0);
		}
		i += fstore[(int)ins->op.opcode](ar, ins->params[arg], i);
	}
	return (i - start);
}

int				get_instruction(char *arena, t_op *tab, int i, t_instruction *ins)
{
	char	hex;
	int		arglen;
	int		ret;


	hex = *(arena + (i >= MEM_SIZE ? 0 : i));
	if (!(ret = is_valid_opcode(hex)))
		return (0);
	else
		ft_memmove(ins->op, tab[ret]);
	hex = *(arena + (i + 1) >= MEM_SIZE ? 1 : i + 1);
	if (!(ins->op.ocp = is_valid_ocp(hex, ins->op, ins->params))
		return (0);
	if (!(ins->params.nb_bytes = store_arg(arena, ins, i, ins->op.ocp))
		return (0);
//	ft_printf("valid opcode! = %d in index %d\n", ins->op, i)
	arg = ins->param;
	arglen = arg[0].nb_bytes + arg[1].nb_bytes + arg[2].nb_bytes;
	return (1 + needs_ocp(ins->op) + arglen);
}

int			launch_instruction(char *arena, int *pc)
{
	t_instruction	ins;
	int				ret;

	ft_bzero(ins, sizeof(*ins));
	
	static int 	(*f_ins[NB_INSTRUCTIONS + 1])(t_vm *vm, t_process *proc,
			t_arg arg[3]) = {NULL, &ins_live, &ins_ld,
		&ins_st, &ins_add, &ins_sub, &ins_and, &ins_or, &ins_xor, &ins_zjmp,
		&ins_ldi, &ins_sti, &ins_fork, &ins_lld, &ins_lldi, &ins_lfork,
		&ins_aff};
	if (ret = get_instruction(arena, *pc, &ins))
	{
		f_ins[ins.op](vm, pr, ins.params);
		*pc += ret;
	}
	else
		*pc += 1;
}


/*


int				get_instruction(t_vm *vm, t_op *tab, t_process *pr)
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
	if (store_argval(vm, (t_arg **)&arg, &tab[opcode], pr))
	{
		ft_printf("valid opcode! = %d in index %d\n", opcode, pr->pc);
		ins[opcode](vm, pr, arg);
		pr->pc = (1 + needs_ocp(opcode) + arg[FIRST].nb_bytes
			+ arg[SECOND].nb_bytes + arg[THIRD].nb_bytes) % MEM_SIZE;
		return (opcode);
	}
	return (0);
}
*/
