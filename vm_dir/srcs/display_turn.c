#include "vm.h"

void	last_live(t_vm *vm, t_process *proc)
{
	(void)vm;
	ft_printf(">>> %s ", proc->id);
}


void	cycle_end(t_vm *vm, t_process *proc)
{
	(void)proc;
	(void)vm;
	ft_printf("\n%s | ", MSG_CYCLE_END);
}

void	move_one(t_vm *vm, t_process *proc)
{
	(void)vm;
	(void)proc;
	ft_printf("%-*s ", PAD_INS, MSG_MOVE_ONE);
}

void	cycle_nb(t_vm *vm, t_process *proc)
{
	(void)proc;
	ft_printf("\n%s%s [ %d ] %s\n", COLF_BGREY, MSG_CYCLES_REMAINING, CYCLE_TO_DIE - vm->cycle, COLF_OFF);
}

void	turn_player(t_vm *vm, t_process *proc)
{
	(void)vm;
	ft_printf("PLAYER %-*d aka %-*s", PAD_PLNUM, proc->id, PAD_PLNAME, proc->name); 
}
