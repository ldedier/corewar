/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inst_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uboumedj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 16:42:17 by uboumedj          #+#    #+#             */
/*   Updated: 2018/12/16 16:42:17 by uboumedj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

/*
** check_reg function checks if the given int parameter is a valid reg value.
*/

int		check_reg(int r)
{
  if (r < 0 || r >= REG_NUMBER)
    return (0);
  return (1);
}
