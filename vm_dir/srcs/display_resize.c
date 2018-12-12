#include "vm.h"

void	lives_turn(void *content)
{
	t_vm *vm ;

	vm = (t_vm *)content;
	ft_printf("%s %d", MSG_NBR_LIVES_TURN, vm->live.total_pl);
	ft_printf(" %s %d\n", MSG_RESIZE, vm->c_to_die);
}

void	cycles_to_autoresize(void *content)
{
	t_vm *vm;

	vm = (t_vm *)content;
	ft_printf("%d %s\n", vm->checks - 1, MSG_NBR_TO_AUTORESIZE);
}

void	resize(void *content)
{
	t_vm *vm;

	vm = (t_vm *)content;
	ft_printf("%s %d\n", MSG_RESIZE, vm->c_to_die);
}

