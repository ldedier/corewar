#include "vm.h"

void	last_live(t_vm *vm, int pl)
{
	t_process	*proc;

	proc = get_proc_num(vm->proc, pl);
	ft_printf(">>> %s ", proc->id);
}


void	cycle_end(t_vm *vm, int pl)
{
	(void)pl;
	(void)vm;
	ft_printf("\n%s | ", MSG_CYCLE_END);
}

void	move_one(t_vm *vm, int pl)
{
	(void)vm;
	(void)pl;
	ft_printf("%-*s ", PAD_INS, MSG_MOVE_ONE);
}

void	cycle_nb(t_vm *vm, int pl)
{
	(void)pl;
	ft_printf("\n%s %s [ %d ] \n", LABEL_CYCLE, MSG_CYCLES_REMAINING, CYCLE_TO_DIE - vm->cycle);
}

