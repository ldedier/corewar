/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 15:50:38 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/08 18:33:52 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	corehub_port_and_address(t_vm *vm, int argc, char **argv, int *cur)
{
	long long int	nb;
	int				i;

	vm->client.active = 1;
	if (*cur + 2 > argc)
		ft_error_exit(INSUF_INFO_CH);
	*cur += 1;
	vm->client.server_address = argv[*cur];
	*cur += 1;
	i = 0;
	while (argv[*cur][i])
	{
		if (!(ft_strchr("0123456789", argv[*cur][i])))
			ft_error_exit(INVALID_PORT);
		i++;
	}
	nb = ft_atoll(argv[*cur]);
	if (nb > 2147483647)
		ft_error_exit(INVALID_PORT);
	vm->client.port = nb;
}
