/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 17:44:16 by ldedier           #+#    #+#             */
/*   Updated: 2018/11/30 13:20:59 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	t_op op;
	op = g_op_tab[0];
	ft_printf("%s\n", op.description);
	return (0);
}
