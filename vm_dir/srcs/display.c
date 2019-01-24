/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 21:43:44 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/24 19:46:16 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"


void		display_proc_ins(t_process *proc, int val1, int val2, int val3)
{
	int i;
	int type;
	int	val[3];

//	if (vm->visu.active || !(vm->display & MSG_INS))
//		return ;
	i = -1;
	val[0] = val1;
	val[1] = val2;
	val[2] = val3;
	ft_printf("P%5d | %s", proc->nb, proc->pending_ins.op.instruction_name);
	while (++i < proc->pending_ins.op.nb_params)
	{
		type = proc->pending_ins.params[i].type;
		ft_printf(" %s%d", type == REG_CODE ? "r" : "", val[i]);
	}
}

void		display_player_intro(t_player *player)
{
	ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
			player->num,
			player->algo_len,
			player->name,
			player->comm[0] ? player->comm : ""); // verifier si inverse player num ou si ordre d'entree quel que soit le nom
}

void		display_resize(t_vm *vm)
{
	if (!vm->visu.active && vm->display & (1 << MSG_CYCLE))
		ft_printf("Cycle to die is now %d\n", vm->c_to_die);
}

void		display_player_alive(t_vm *vm, t_process *proc)
{
	if (!vm->visu.active && vm->display & (1 << MSG_LIVE))
		ft_printf("\nPlayer %d (%s) is said to be alive",
				-proc->player->num,
				proc->player->name);
}

void		display_last_live(t_vm *vm, t_process *proc)
{
	if (!vm->visu.active && vm->display & (1 << MSG_DEATH))
		ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n",
				proc->nb,
				vm->total_cycle - proc->live_cycle,
				vm->c_to_die);
}

void		display_cycle(t_vm *vm)
{
	if (!vm->visu.active && vm->display & (1 << MSG_CYCLE))
		ft_printf("It is now cycle %d\n", vm->total_cycle);
}

void		display_winner(t_vm *vm)
{
	ft_printf("Contestant %d, ", -vm->winner->num);
	ft_putchar('"');
	ft_printf("%s", vm->winner->name);
	ft_putchar('"');
	ft_printf(", has won !\n");
}

void		display_move(t_vm *vm, t_process *proc)
{
	int i;
	int	j;
	int	var_len;
	if (vm->visu.active || !(vm->display & (1 << MSG_MOVE)))
		return ;
	if (proc->pending_ins.op.opcode == ZJMP && proc->carry)
		return ;
	i = -1;
	ft_printf("ADV %d (0x%04x -> 0x%04x)", proc->ins_bytelen, proc->pc, (proc->pc + proc->ins_bytelen % MEM_SIZE));
	ft_printf(" %02x", (unsigned char)proc->pending_ins.op.opcode);
	if (proc->pending_ins.op.has_ocp)
	ft_printf(" %02x", (unsigned char)proc->pending_ins.ocp);
	var_len = 0;
	while (++i < proc->pending_ins.op.nb_params)
	{
		j = 0;
		while (++j <= proc->pending_ins.params[i].nb_bytes)
		{
			ft_printf(" %02x", (unsigned char)(vm->arena[proc->pc + proc->pending_ins.op.has_ocp + var_len + j]));
		}
		var_len += proc->pending_ins.params[i].nb_bytes;
	}
	ft_printf(" \n");
}

void		display_registers(t_vm *vm)
{
	int		i;
	t_list	*proc_lst;

	proc_lst = vm->proc;
	ft_printf("*** DISPLAY REGISTERS ***\n\n");
	while (proc_lst && proc_lst->content)
	{
		i = -1;
		while (++i < REG_NUMBER && proc_lst->content)
			ft_printf("R%d: %d | ", i + 1, ((t_process *)proc_lst->content)->reg[i]);
		ft_printf("\n\n");
		proc_lst = proc_lst->next;
	}
}
