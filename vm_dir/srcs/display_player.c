#include "vm.h"

void	pl_death(t_vm *vm, t_process *proc)
{
	(void)vm;
	ft_printf("%s %d %s\n", LABEL_PLAYER, proc->id, MSG_DEATH);
}

void	pl_live(t_vm *vm, t_process *proc)
{
	(void)vm;
	ft_printf(" >>>%s", proc->id);
}

void	pl_victory(t_vm *vm, t_process *proc)
{
	(void)vm;
	ft_printf("%s %s %d [%s] \n", MSG_VICTORY, LABEL_PLAYER, proc->id, proc->name);
}

void	pl_cycle(t_vm *vm, t_process *proc)
{
	(void)vm;
	ft_printf(".... %d", proc->cycle);
}

void	pl_pc(t_vm *vm, t_process *proc)
{
	(void)vm;
	ft_printf("[%d]", proc->pc);
}
