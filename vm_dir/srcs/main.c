/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uboumedj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 17:19:23 by uboumedj          #+#    #+#             */
/*   Updated: 2018/12/04 22:12:30 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**Yo cette fonction me sert à tester chaque composant des structures
**pour être sûr que tout va bien lors de la lecture/parsing. Comme son nom
**l'indique c:
*/

void	test(t_vm vm, int argc, char **argv)
{
	int		i;
	int		j;
	char	*name;
	char	*comm;
	char	*algo;

	i = 0;
	ft_printf("There are %d player(s)\n", vm.nb_players);
	while (i < vm.nb_players)
	{
		ft_printf("player %d has been assigned the number %d ", i + 1,
				vm.player[i].num);
		ft_printf("and his .cor is %s\n", argv[vm.player[i].prog]);
		ft_printf("As a string, the contents of the .cor are: \n");
		j = 0;
		while (j++ < TOT_SIZE)
		{
			ft_printf("%c", vm.player[i].bin[j]);
		}
		ft_printf("\n");
		name = vm.player[i].name;
		comm = vm.player[i].comm;
		algo = vm.player[i].algo;
		ft_printf("The name of the champion is: %s\n", name);
		ft_printf("The comment is: %s\n", comm);
		ft_printf("The algorithm hex information is: \n");
		j = 0;
		while (j < CHAMP_MAX_SIZE)
		{
			ft_printf("%02x ", algo[j]);
			j++;
		}
		ft_printf("\n");
		i++;
	}
	if (vm.dump != 0)
	{
		ft_printf("There is a dump flag with number %d\n", vm.dump);
	}
	i = 0;
	j = 0;
	ft_printf("\nARENA\n\n");
	while (i < MEM_SIZE)
	{
		ft_printf("%02x", 0xFF & vm.arena[i].hex);
		i++;
		j++;
		if (j == 64)
		{
			ft_printf("\n");
			j = 0;
		}
		else
			ft_printf(" ");
	}
	ft_printf("\n");
	(void)argc;
}

int		main(int argc, char **argv)
{
	t_vm	vm;

	if (argc <= 1)
		error_exit(1);
	if (!check_type(argc, argv))
		error_exit(2);
	init_vm(&vm, argv);
	flags(&vm, argc, argv);
	read_files(&vm);
	parse(&vm);
	dispatch_players(&vm);
	test(vm, argc, argv);
	return (0);
}
