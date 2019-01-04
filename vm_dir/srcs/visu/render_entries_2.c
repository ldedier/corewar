/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_phase.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 19:07:54 by ldedier           #+#    #+#             */
/*   Updated: 2019/01/03 15:47:50 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		ft_render_cycle_to_die(t_vm *vm, int y)
{
	char	*value;

	if (!(value = ft_itoa(vm->c_to_die)))
		return (1);
	if (ft_render_entry(vm, "cycle to die", value, y))
		return (1);
	return (0);
}

int		ft_render_cycle_delta(t_vm *vm, int y)
{
	char	*value;

	if (!(value = ft_itoa(CYCLE_DELTA)))
		return (1);
	if (ft_render_entry(vm, "cycle delta", value, y))
		return (1);
	return (0);
}


int		ft_render_ctd_countdown(t_vm *vm, int y)
{
	char	*tmp;
	char	*tmp2;
	char	*value;

	int val = 42; //NEED VARIABLE
	if (!(tmp = ft_itoa(val)))
		return (1);
	if (!(tmp2 = ft_itoa(vm->c_to_die)))
	{
		free(tmp);
		return (1);
	}
	if (!(value = ft_strjoin_3(tmp, "/", tmp2)))
	{
		free(tmp);
		free(tmp2);
		return (1);
	}
	if (ft_render_entry(vm, "CTD countdown", value, y))
		return (1);
	return (0);
}

int		ft_render_lives_current_period(t_vm *vm, int y)
{
	char	*tmp;
	char	*tmp2;
	char	*value;

	int val = 42; //NEED VARIABLE
	if (!(tmp = ft_itoa(val)))
		return (1);
	if (!(tmp2 = ft_itoa(NBR_LIVE)))
	{
		free(tmp);
		return (1);
	}
	if (!(value = ft_strjoin_3(tmp, "/", tmp2)))
	{
		free(tmp);
		free(tmp2);
		return (1);
	}
	free(tmp);
	free(tmp2);
	if (ft_render_entry(vm, "lives in current period", value, y))
		return (1);
	return (0);
}

int		ft_render_checks(t_vm *vm, int y)
{
	char	*tmp;
	char	*tmp2;
	char	*value;

	int val = vm->checks;
	if (!(tmp = ft_itoa(val)))
		return (1);
	if (!(tmp2 = ft_itoa(MAX_CHECKS)))
	{
		free(tmp);
		return (1);
	}
	if (!(value = ft_strjoin_3(tmp, "/", tmp2)))
	{
		free(tmp);
		free(tmp2);
		return (1);
	}
	if (ft_render_entry(vm, "number of checks", value, y))
		return (1);
	return (0);
}
