#include "vm.h"

void	cycle_end(void *content)
{
	t_vm *vm;

	vm = (t_vm *)content;
	ft_printf("\n%s%s%s%s%s | ", COL_FCYCLE, COL_BCYCLE, MSG_CYCLE_END, COLF_OFF, COLB_OFF);
}

void	move_one(void *content)
{
	(void)content;
	ft_printf("%s%s%s ", COLF_OFF, MSG_MOVE_ONE, COLF_OFF);
}

void	cycle_nbr(void *content)
{
	t_vm *vm;
	
	vm = (t_vm *)content;
	ft_printf("\n%s%s%d [ %d %s ] %s\n", COLF_BGREY, LABEL_CYCLE, cycle,MSG_ CYCLES_REMAINING, vm->c_to_die - cycle, COLF_OFF);
}

