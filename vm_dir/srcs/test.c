/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uboumedj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 17:19:23 by uboumedj          #+#    #+#             */
/*   Updated: 2018/12/06 22:44:37 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**player_num basically tests the assignment of each number to each player
*/

static void		player_num(t_vm vm, int i)
{
	int		j;

	j = 0;
	ft_printf("player %d has been assigned the number %d ", i + 1,
			vm.player[i].num);
	ft_printf("and his .cor is %s\n", vm.player[i].cor_name);
	ft_printf("\n");
}

/*
**parsing tests if each player part was parsed correctly
*/

static void		parsing(t_vm vm, int i)
{
	char	*name;
	char	*comm;
	char	*algo;
	int		j;

	name = vm.player[i].name;
	comm = vm.player[i].comm;
	algo = vm.player[i].algo;
	ft_printf("The name of the champion is: [%s]\n", name);
	ft_printf("The comment is: [%s]\n", comm);
	ft_printf("The algorithm hex information is:\n");
	j = 0;
	while (j < CHAMP_MAX_SIZE)
	{
		ft_printf("%.02x ", 0xFF & algo[j]);
		j++;
	}
	ft_printf("\n");

}

/*
**basic testing for the parsing/saving of variables inside structures
*/

void					test(t_vm vm)
{
	int		i;
	i = 0;
	ft_printf("There are %d player(s)\n", vm.nb_players);
	while (i < vm.nb_players)
	{
		player_num(vm, i);
		parsing(vm, i);
		i++;
	}
	if (vm.dump != 0)
		ft_printf("There is a dump flag with number %d\n", vm.dump);
	display_arena(vm.arena);
}
