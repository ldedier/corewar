/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 21:43:44 by emuckens          #+#    #+#             */
/*   Updated: 2019/02/13 21:09:48 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"


void		display_proc_ins(t_vm *vm, t_process *proc)
{
	int i;
	int arg_type;
	int	val;

	if (!(vm->display & (1 << MSG_INS)))
		return ;
	i = -1;
	ft_printf("\nP %4d | %s", proc->nb, proc->pending_ins.op->instruction_name);
	while (++i < proc->pending_ins.op->nb_params)
	{
		if (proc->pending_ins.params[i].retrieval_mode)
			ft_printf(" %d", proc->pending_ins.params[i].dest_value);
		else
		{
			val = proc->pending_ins.params[i].value;
			arg_type = proc->pending_ins.params[i].type;
			if (!(proc->pending_ins.op->opcode == ST && i == 1)) // pas reussi a gerer autrement octobre rouge st r1 3 en 3265
				ft_printf(" %s%d", arg_type == REG_CODE ? "r" : "", val);
			else
				ft_printf(" %d", val);

		}
	}
}

void		display_player_intro(t_player *player)
{
	ft_printf("\n* Player %d, weighing %d bytes, \"%s\" (\"%s\") !",
			player->num_type * player->num,
			player->algo_len,
			player->name,
			player->comm[0] ? player->comm : ""); 
}

void		display_resize(t_vm *vm)
{
	if (vm->display & (1 << MSG_CYCLE))
		ft_printf("\nCycle to die is now %d", vm->c_to_die);
}

void		display_player_alive(t_vm *vm, t_player *player)
{
	if (vm->display & (1 << MSG_LIVE))
		ft_printf("\nPlayer %d (%s) is said to be alive", player->num_type * player->num, player->name);
}

void		display_last_live(t_vm *vm, t_process *proc)
{
	if (vm->display & (1 << MSG_DEATH))
		ft_printf("\nProcess %d hasn't lived for %d cycles (CTD %d)",
				proc->nb,
				vm->total_cycle - proc->live_cycle,
				vm->c_to_die);
}

void		display_cycle(t_vm *vm)
{
	if (vm->display & (1 << MSG_CYCLE))
		ft_printf("\nIt is now cycle %d", vm->total_cycle);
}

void		display_winner(t_vm *vm)
{
	ft_printf("\nContestant %d, ", -vm->winner->num);
	ft_putchar('"');
	ft_printf("%s", vm->winner->name);
	ft_putchar('"');
	ft_printf(", has won !\n");
}

void		display_move(t_vm *vm, t_process *proc)
{
	int i;
	int len;

	len = ft_abs(proc->ins_bytelen);

	if (!(vm->display & (1 << MSG_MOVE)))
		return ;
	if (proc->pending_ins.op->opcode == ZJMP && proc->carry)
		return ;
	proc->pc = mod(proc->pc, MEM_SIZE);
	ft_printf("\nADV %d (0x%04x -> 0x%04x) ", len, proc->pc, (proc->pc + len));
	i = -1;
	while (++i < len)
		ft_printf("%02x ", (unsigned char)(vm->arena[mod(proc->pc + i, MEM_SIZE)]));
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
