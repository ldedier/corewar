/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uboumedj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 17:19:23 by uboumedj          #+#    #+#             */
/*   Updated: 2018/11/23 16:38:00 by uboumedj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

/*
**Yo cette fonction me sert à tester chaque composant des structures
**pour être sûr que tout va bien lors de la lecture/parsing. Comme son nom
**l'indique c: 
*/

void	test(t_vm vm, int argc, char **argv)
{
	int		i;
	int		j;

	i = 0;
	ft_printf("There are %d player(s)\n", vm.nb_players);
	while (i < vm.nb_players)
	{
		ft_printf("player %d has been assigned the number %d ", i + 1,
				vm.player[i].num);
		ft_printf("and his .cor is %s\n", argv[vm.player[i].prog]);
		ft_printf("The contents of the .cor are: \n");
		j = 0;
		while (j++ < TOT_SIZE)
		{
			ft_printf("%c", vm.player[i].bin[j]);
		}
		ft_printf("\n");
		i++;
	}
	if (vm.dump != 0)
	{
		ft_printf("There is a dump flag with number %d\n", vm.dump);
	}
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
	test(vm, argc, argv);
	return (0);
}
