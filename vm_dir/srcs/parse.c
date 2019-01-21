/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uboumedj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 18:41:42 by uboumedj          #+#    #+#             */
/*   Updated: 2019/01/21 20:10:40 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** name_and_comm static function is used by the parse function to save
** the name and the comment of given files into their respective arrays in each
** player's structure: player[x].name and player[x].comm
*/

static void		name_and_comm(t_vm *vm, int i)
{
	int		n;
	char	*name;
	char	*comm;
	char	*bin;

	n = 0;
	bin = vm->player[i].bin;
	name = vm->player[i].name;
	comm = vm->player[i].comm;
	while (n < PROG_NAME_LENGTH)
	{
		name[n] = bin[n + 4];
		n++;
	}
	name[n] = 0;
	n = 0;
	while (n < COMMENT_LENGTH)
	{
		comm[n] = bin[n + 12 + PROG_NAME_LENGTH];
		n++;
	}
	comm[n] = 0;
}

/*
** check_head_size static function checks the size given in the .cor's
** header. If it doesn't match the real size of the instructions, the program
** will output an error message and exit.
*/

static void		check_head_size(t_vm *vm, int i)
{
	char	*bin;
	char	size[4];
	int		n;

	bin = vm->player[i].bin;
	n = 0;
	while (n < 4)
	{
		size[3 - n] = bin[PROG_NAME_LENGTH + 8 + n];
		n++;
	}
	vm->player[i].header_size = *(int *)size;
}

/*
** instructions static function is used by the parse function to add the [algo]
** part (the instructions) inside the player structure. It also checks if the
** instructions part exceeds the max allowed size CHAMP_MAX_SIZE.
*/

static void		instructions(t_vm *vm, int i)
{
	char	*algo;
	char	*bin;
	int		n;

	algo = vm->player[i].algo;
	bin = vm->player[i].bin;
	n = 0;
	while (PROG_NAME_LENGTH + 16 + COMMENT_LENGTH + n < vm->player[i].file_len)
	{
		algo[n] = bin[PROG_NAME_LENGTH + 16 + COMMENT_LENGTH + n];
		n++;
	}
	vm->player[i].algo_len = n;
	check_head_size(vm, i);
	if (n != vm->player[i].header_size)
		error_exit_msg(WRG_HEAD_SIZE);
	if (n > CHAMP_MAX_SIZE)
		error_exit_msg(MAX_CHAMP);
	while (n < CHAMP_MAX_SIZE)
	{
		algo[n] = 0;
		n++;
	}
}

/*
** parse function tries to parse each player's binary data to retrieve their
** information, i.e the [name], which is the name of the champion, the [comm],
** containing the commentary, and the [algo] containing the instructions.
*/

void			parse(t_vm *vm)
{
	int		i;

	i = 0;
	while (i < vm->nb_players)
	{
		ft_printf("-");
		name_and_comm(vm, i);
		instructions(vm, i);
		i++;
	}
}

/*
** read_files function reads each given file and stores their content inside
** their respective [bin] components in each player's structure.
*/

int				read_files(t_vm *vm)
{
	int		i;

	i = 0;
	while (i < vm->nb_players)
	{
		if (ft_read_player(vm->player[i].cor_name, &(vm->player[i])))
			return (1);
		i++;
	}
	return (0);
}
