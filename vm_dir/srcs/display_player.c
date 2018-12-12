#include "vm.h"

void	pl_death(t_vm *vm, int pl)
{
	t_process *proc;

	proc = get_proc_num(vm->proc, pl);
	ft_printf("%d %d %s \n", proc->id, MSG_DEATH);
}

void	pl_live(t_vm *vm, int pl)
{
	(void)pl;
	t_process	*proc;

	proc = get_proc_num(vm->proc, pl);
	ft_printf(" >>>%s", proc->id);
}

void	pl_victory(t_vm *vm, int pl)
{
	(void)pl;
	ft_printf("%s %s%s %d [%s] %s%s\n", MSG_VICTORY, vm->color[(NB_GAME_MSG + vm->nb_players - vm->live.last_pl) * 2 + 1], LABEL_PLAYER, vm->nb_players - vm->live.last_pl, vm->player[vm->live.last_pl].name, COLF_OFF, COLB_OFF);
}

void	pl_cycle(t_vm *vm, int pl)
{
	t_process *proc;
	
	proc = get_proc_num(vm->proc, pl);
	ft_printf(".... %d", proc->cycle);
}

void	pl_pc(t_vm *vm, int pl)
{
	t_process *proc;

	proc = get_proc_num(vm->proc, pl);
	ft_printf("[%d]\n", proc->pc);
}

