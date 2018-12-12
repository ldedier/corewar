#include "vm.h"

void	pl_death(void *content)
{
	t_process *proc;

	proc = (t_process *)content;
	ft_printf("%s%s %d %d %s %s%s\n", COL_FDEAD, COL_BDEAD, proc->num, MSG_DEATH, COLF_OFF, COLB_OFF);
}

void	pl_live(void *content)
{
	t_vm *vm;
	
	vm = (t_vm *)content;
	ft_printf(" %s>>>%s %s%s%s", COL_VALIDINS, COLF_OFF, vm->color.player[vm->live.last_pl * 2 + 1], vm->player[vm->live.last_pl].name, COLB_OFF);
}

void	pl_victory(void *content)
{
	t_vm *vm;

	vm = (t_vm *)content;
	ft_printf("%s %s%s %d [%s] %s%s\n", MSG_VICTORY, vm->color.player[(vm->nb_players - vm->live.last_pl) * 2 + 1], LABEL_PLAYER, vm->nb_players - vm->live.last_pl, vm->player[vm->live.last_pls].name, COLF_OFF, COLB_OFF);
}

void	pl_cycle(void *content)
{
	t_process *proc;
	
	proc = (t_process *)content;
	ft_printf("%s.... %d%s", COL_WAIT, proc->cycle, COLF_OFF);
}

void	pl_pc(void *content)
{
	t_process *proc;

	proc = (t_process *)content;
	ft_printf(" %*s[%d]\n", "", proc->pc);
}

