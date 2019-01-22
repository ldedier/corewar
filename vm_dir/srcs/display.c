/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 21:43:44 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/22 16:41:21 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		display_player_intro(t_vm *vm, t_player *player)
{
	(void)vm;
	ft_printf("* Player %d, weighing %d bytes, ",
			-player->num,
			player->algo_len); // verifier si inverse player num ou si ordre d'entree quel que soit le nom
	ft_putchar('"');
	ft_printf("%s", player->name);
	ft_putchar('"');
	if (player->comm[0])
	{
		ft_printf(" (");
		ft_putchar('"');
		ft_printf("%s", player->comm);
		ft_putchar('"');
		ft_printf(") !\n");
	}
}

void		display_ins(t_vm *vm, t_process *proc)
{
	int		i;

	(void)vm;
	if (!proc)
		return ;
//	if (!proc || vm->visu.active || !(vm->display & (1 << 1)))
//		return ;
	i = -1;
	ft_printf("P%5d | %s", proc->nb, proc->pending.ins.op.instruction_name);
	while (++i < proc->pending.ins.op.nb_params)
	{
		ft_putchar(' ');
		if (proc->pending.ins.params[i].type == T_REG)
			ft_printf("r");
		ft_printf("%d", proc->pending.ins.params[i].value);
	}
	ft_printf("\n");
}


void		display_last_live(t_vm *vm, t_process *proc)
{
//	if (vm->visu.active)
//		return ;
	ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n", proc->nb, vm->total_cycle - proc->live_cycle, vm->c_to_die);

}

void		display_cycle(t_vm *vm, t_process *proc)
{
	(void)proc;
//	if (vm->visu.active || !(vm->display & (1 << 1)))
//		return ;
	ft_printf("It is now cycle %d\n", vm->total_cycle);
}

void		display_winner(t_vm *vm, t_process *proc)
{
	(void)proc;
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
	(void)vm;
//	if (vm->visu.active || !(vm->display & (1 << 2)))
//		return ;
	i = -1;
	ft_printf("ADV %d (0x%04x -> 0x%04x)", proc->ins_bytelen, proc->pc, (proc->pc + proc->ins_bytelen % MEM_SIZE));
	ft_printf(" %02x", (unsigned char)proc->pending.ins.op.opcode);
	if (proc->pending.ins.op.has_ocp)
	ft_printf(" %02x", (unsigned char)proc->pending.ins.ocp);
	var_len = 0;
	while (++i < proc->pending.ins.op.nb_params)
	{
		j = 0;
		while (++j <= proc->pending.ins.params[i].nb_bytes)
		{
			ft_printf(" %02x", (unsigned char)(vm->arena[proc->pc + proc->pending.ins.op.has_ocp + var_len + j]));
		}
		var_len += proc->pending.ins.params[i].nb_bytes;
	}
	ft_printf(" \n");
}
/*
void		display_live_player(t_vm *vm, int op_code)
{
	t_player *player;

	if (op_code == LIVE)
	{
		player = get_player_num(vm->proc, vm->winner->num);
		display(vm, NULL, LAST_LIVE);
	}
}

void		display_ins_description(t_vm *vm, char *str, int opcode)
{
	ft_printf("%s >>> %*-s%s", COLF_CYAN, PAD_INS - 5, str, COLF_OFF);
	display_live_player(vm, opcode);
}
*/
void		display_registers(t_vm *vm, t_process *proc)
{
	int		i;
	t_list	*proc_lst;

	(void)proc;
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

void		display(t_vm *vm, t_process *proc, int type)
{
	static void (*display[NB_GAME_MSG][2])(t_vm *vm, t_process *proc) = {
		{&display_cycle, NULL},
	   	{&display_ins, NULL},
	   	{&display_last_live, NULL},
		{&display_move, NULL},
		{&display_registers, NULL},
		{&display_winner, NULL}};

	display[type][(int)vm->visu.active](vm, proc);
}
