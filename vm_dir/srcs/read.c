/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uboumedj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 16:42:17 by uboumedj          #+#    #+#             */
/*   Updated: 2018/12/05 17:17:00 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**check_length static function is used by read_files to check the length of
**each file before storing it inside a structure, to avoid exceeding TOT_SIZE.
*/

static int	check_length(t_vm *vm, int num)
{
	char	buffer[BUFF_SIZE + 1];
	int		fd;
	int		check;


	vm->player[num].file_len = 0;
	if ((fd = open(vm->player[num].cor_name, O_RDONLY)) == -1)
		error_exit_msg(FILE_ISSUE);
	while ((check = read(fd, buffer, BUFF_SIZE)))
		vm->player[num].file_len += check;
	if (vm->player[num].file_len > TOT_SIZE)
		error_exit_msg(FILE_TOO_BIG);
	close(fd);
	return (vm->player[num].file_len);
}

/*
**check_magic static function is used at the end of each read_files iteration
**to check if the magic number at the beginning of the file matches the correct
**magic number for a corewar .cor file, which is 0xea83f3.
*/

static int	check_mgc(t_vm *vm, int i)
{
	int		mgc;
	char	*bin;

	bin = vm->player[i].bin;
	mgc = (((bin[0] & 0xFF) << 24) | ((bin[1] & 0xFF) << 16) |
					((bin[2] & 0xFF) << 8) | (bin[3] & 0xFF));
	return (mgc == COREWAR_EXEC_MAGIC);
}

/*
**read_files function reads each given file and stores their content inside
**the respective [bin] components of each player's structure.
*/

void		read_files(t_vm *vm)
{
	int		i;
	int		fd;
	int		len;

	i = 0;
	while (i < vm->nb_players)
	{
		len = check_length(vm, i);
		if ((fd = open(vm->player[i].cor_name, O_RDONLY)) == -1)
			error_exit_msg(FILE_ISSUE);
		if ((read(fd, vm->player[i].bin, vm->player[i].file_len)) == -1)
			error_exit_msg(FILE_ISSUE);
		vm->player[i].bin[len] = '\0';
		close(fd);
		if (!check_mgc(vm, i))
			error_exit_mgc(vm->player[i].cor_name);
		i++;
	}
}
