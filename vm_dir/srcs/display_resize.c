#include "vm.h"

void	lives_turn(t_vm *vm, t_process *proc)
{
	(void)proc;
	ft_printf(" %s %d\n", MSG_RESIZE, vm->c_to_die);
}

void	cycles_to_autoresize(t_vm *vm, t_process *proc)
{
	(void)proc;
	ft_printf("%d %s\n", vm->checks - 1, MSG_NBR_TO_AUTORESIZE);
}

void	resize(t_vm *vm, t_process *proc)
{
	(void)proc;
	ft_printf("%s %d\n", MSG_RESIZE, vm->c_to_die);
}

