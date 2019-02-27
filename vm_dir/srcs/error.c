/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uboumedj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 17:22:33 by uboumedj          #+#    #+#             */
/*   Updated: 2019/02/27 17:03:59 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/* UTILISEE OU???
**
** error_exit_mgc function outputs an error message if a file is given with
** the wrong magic number at the beginning, then exits the program.
*/
/*
void		error_exit_mgc(char *name)
{
	ft_putstr_fd("File ", 2);
	ft_putstr_fd(name, 2);
	ft_putstr_fd(" has wrong magic number and is therefore not readable\n", 2);
	exit(1);
}
*/
/*
** error_exit_msg and ft_error_exit functions output the error message
** specified in error.h used during its call, then exits the program.
*/

int		error_exit_msg(t_vm *vm, const char *str)
{
	clear_vm(vm);
	ft_dprintf(2, "%s\n", str);
	while (1);
	return (1);
//	exit(1);
}


/*
** check_type function checks the extension of the files ./corewar received
** and sends an error if the type doesn't match a .cor file.
*/

int			check_type(int ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (((!ft_strcmp("-dump", av[i]) || !ft_strcmp("-n", av[i])) &&
				i + 1 < ac))
			i += 2;
		else if (!ft_strcmp("-w", av[i]) && i + 2 < ac)
			i += 3;
		else if (!ft_strcmp("-v", av[i]) && i + 1 < ac)
			i++;
		else if (!ft_strcmp("-c", av[i]) && i + 1 < ac)
			i++;
		else if (ft_is_of_extension(av[i], ".cor"))
			i++;
		else if (av[i][0] == '-' && ft_isdigit(av[i][1]))
			++i;
		else
			return (0);
	}
	return (1);
}

/*
** check_header function checks the op.h header file's global variables for any
** illogical declarations.
*/

int			check_header(t_vm *vm)
{
	if (MAX_PLAYERS != 4)
		return (error_exit_msg(vm, ERR_HEADER));
	if (MEM_SIZE < MAX_PLAYERS * 1024)
		return (error_exit_msg(vm, ERR_HEADER));
	if (CHAMP_MAX_SIZE > MEM_SIZE / MAX_PLAYERS)
		return (error_exit_msg(vm, ERR_HEADER));
	return (SUCCESS);
}
