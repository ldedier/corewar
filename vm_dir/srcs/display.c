#include "vm.h"

static void	display_player_msg(t_vm *vm, t_process *proc, int type)
{
	static void	*content[NB_MSG_PLAYERS] = {proc, vm, vm, proc};
	static void	(*display[NB_MSG_PLAYERS])(void *content) = {&pl_cycle, pl_live,
		&pl_death, &pl_victory};
	
	color_on(vm->color, type * 2);
	display[type](content[type]);
	color_off();
}

static void	display_resize_msg(t_vm *vm, t_process *proc, int type)
{	
	(void)proc;
	static void (*display[MSG_NB_MSG_RESIZE])(void *content) = {&lives_turn,
		&cycles_to_autoresize, &resize};
	
	color_on(vm, NB_MSG_PLAYER + type * 2);
	display[type](vm); 
	color_off();

}

static void	display_turn_msg(t_vm *vm, t_process *proc, int type)
{
	static void	*content[NB_MSG_TURN] = {NULL, proc, vm, vm};
	static void	(*display[NB_MSG_TURN])(void *content) = {&move_one, &proc_pc, &cycle_nbr, &cycle_end};


	color_on(vm, NB_MSG_PLAYER + NB_MSG_RESIZE + type * 2);
	display[type](content[type]);
}

void	display(t_vm *vm, t_process *proc, int type, int msg)
{
	static int [NB_MSG_TOTAL];
	static void (*display)[NB_MSG_TYPES](t_vm *vm, t_process *proc, int msg) = {display_player, display_resize, display_turn};
	
	display[type](vm, proc, msg);
}
