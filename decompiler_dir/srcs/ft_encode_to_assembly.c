/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_encode_to_assembly.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 00:08:01 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/08 00:08:01 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "decompiler.h"

int		ft_encode_to_assembly(t_env *e)
{
	ft_printf(".name:\"%s\"\n", e->player.name);
	ft_printf(".comment:\"%s\"\n", e->player.comm);
	return (0);
}
