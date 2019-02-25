/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 15:50:38 by ldedier           #+#    #+#             */
/*   Updated: 2019/02/25 14:21:50 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		corehub_port_and_address(t_vm *vm, int argc, char **argv, int *cur)
{
	long long int	nb;
	int				i;

	vm->client.active = 1;
	vm->visu.active = 1;
	if (*cur + 2 > argc)
		return (error_exit_msg(vm, INSUF_INFO_CH));
	*cur += 1;
	vm->client.server_address = argv[*cur];
	*cur += 1;
	i = 0;
	while (argv[*cur][i])
	{
		if (!(ft_strchr("0123456789", argv[*cur][i])))
			return (error_exit_msg(vm, INVALID_PORT));
		i++;
	}
	nb = ft_atoll(argv[*cur]);
	if (nb > 2147483647)
		return (error_exit_msg(vm, INVALID_PORT));
	vm->client.port = nb;
	return (SUCCESS);
}
