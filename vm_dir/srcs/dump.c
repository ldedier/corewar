/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 18:15:26 by emuckens          #+#    #+#             */
/*   Updated: 2019/03/06 13:43:44 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** dump_nb_cycles function is called when the -dump flag is used and stores the
** value given by the user in the [dump] component of the [t_vm] structure.
*/

int			dump_nb_cycles(t_vm *vm, int argc, char **argv, int *cur)
{
	long long int	nb;
	int				i;

	*cur += 1;
	if (*cur + 2 > argc && vm->nb_players == 0)
		return (error_exit_msg(vm, WRG_DUMP));
	i = 0;
	while (argv[*cur][i])
	{
		if (!(ft_strchr("-0123456789", argv[*cur][i])))
			return (error_exit_msg(vm, WRG_DUMP));
		i++;
	}
	nb = ft_atoll(argv[*cur]);
	if (nb > 2147483647 || nb < 0)
		nb = -1;
	vm->dump = nb;
	return (SUCCESS);
}

/*
** dump is called in every cycle to check if we have reached the max cycle
** amount set by the [-dump] option
*/

void			dump(t_vm *vm)
{
	int		i;
	int		hex;

	if (vm->dump >= 0 && vm->total_cycle >= vm->dump)
	{
		ft_putchar('\n');
		hex = 0;
		i = 0;
		while (i < MEM_SIZE)
		{
			if (i % 64 == 0)
				ft_printf("0x%04x : ", hex);
			ft_printf("%02x ", 0xFF & vm->arena[i]);
			if (((i + 1) % 64) == 0)
			{
				ft_printf("\n");
				hex += 64;
			}
			i++;
		}
		clear_vm(vm);
		exit(1);
	}
}
