/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uboumedj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 17:22:33 by uboumedj          #+#    #+#             */
/*   Updated: 2018/12/04 22:12:41 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**error_exit function outputs the error message associated with the ID used
**during its call, then exits the program.
*/

void		error_exit(int n)
{
	if (n == 1)
		ft_putstr_fd(
				"Usage: ./corewar [-dump nb] [[-n nb] [-w] champ1.cor] ...\n",
		2);
	else if (n == 2)
		ft_putstr_fd("File type invalid\n", 2);
	else if (n == 3)
		ft_putstr_fd("Wrong arguments after -dump!\n", 2);
	else if (n == 4)
		ft_putstr_fd("[-dump nbr_cycle]: nbr_cycle can't exceed INT_MAX!\n", 2);
	else if (n == 5)
		ft_putstr_fd("Number of players exceeded max amount\n", 2);
	else if (n == 6)
		ft_putstr_fd("Wrong arguments after -n!\n", 2);
	else if (n == 7)
		ft_putstr_fd("[-n nb] :  nb can't exceed INT_MAX or -INT_MAX\n", 2);
	else if (n == 8)
		ft_putstr_fd("Trying to assign a player number already taken\n", 2);
	else if (n == 9)
		ft_putstr_fd("Issue while handling file\n", 2);
	else if (n == 10)
		ft_putstr_fd("Size of the given file is too large to be handled\n", 2);
	else if (n == 11)
		ft_putstr_fd("Incorrect characters were used in the .cor file\n", 2);
	exit(1);
}

/*
**error_exit_mgc function outputs an error message if a file is given with
**the wrong magic number at the beginning, then exits the program.
*/

void		error_exit_mgc(char *name)
{
	ft_putstr_fd("File ", 2);
	ft_putstr_fd(name, 2);
	ft_putstr_fd(" has wrong magic number and is therefore not readable\n", 2);
	exit(1);
}

/*
**error_exit2 function is the second function used to output error messages
**before exiting the program (because error_exit was too long)
*/

void		error_exit2(int n)
{
	if (n == 1)
		ft_putstr_fd("Champion exceeded maximum allowed size\n", 2);
	exit(1);
}

/*
**check_type function checks the extension of the files ./corewar received
**and sends an error if the type doesn't match a .cor file.
*/

int			check_type(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	while (i < ac)
	{
		if ((!ft_strcmp("-dump", av[i]) || !ft_strcmp("-n", av[i]))
			&& i + 2 < ac)
			i += 2;
		else
		{
			if (ft_strlen(av[i]) < 4)
				return (0);
			j = 0;
			while (av[i][j])
				j++;
			if (av[i][j - 1] != 'r' || av[i][j - 2] != 'o'
					|| av[i][j - 3] != 'c' || av[i][j - 4] != '.')
				return (0);
			i++;
		}
	}
	return (1);
}
