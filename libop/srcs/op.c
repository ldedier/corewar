/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaz <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:43:01 by zaz               #+#    #+#             */
/*   Updated: 2018/12/19 16:42:22 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

t_op	g_op_tab[NB_INSTRUCTIONS + 1] =
{
	{"live", ONE, {T_DIR}, LIVE, 10, LIVE_STR, OCP_NO, CARRY_NO, 0},
	{"ld",TWO, {T_DIR | T_IND, T_REG}, LD, 5, LD_STR, OCP_YES, CARRY_YES, 0},
	{"st", TWO, {T_REG, T_IND | T_REG}, ST, 5, ST_STR, OCP_YES, CARRY_NO, 0},
	{"add", THREE, {T_REG, T_REG, T_REG}, ADD, 10, ADD_STR, OCP_YES, CARRY_YES, 0},
	{"sub", THREE, {T_REG, T_REG, T_REG}, SUB, 10, SUB_STR, OCP_YES, CARRY_YES, 0},
	{"and", THREE, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, AND, 6,
		AND_STR, OCP_YES, CARRY_YES, 0},
	{"or", THREE, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, OR, 6,
		OR_STR, OCP_YES, CARRY_YES, 0},
	{"xor", THREE, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, XOR, 6,
		XOR_STR, OCP_YES, CARRY_YES, 0},
	{"zjmp", ONE, {T_DIR}, ZJMP, 20, ZJMP_STR, OCP_NO, CARRY_YES, 1},
	{"ldi", THREE, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, LDI, 25,
		LDI_STR, OCP_YES, CARRY_NO, 1},
	{"sti", THREE, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, STI, 25,
		STI_STR, OCP_YES, CARRY_NO, 1},
	{"fork", ONE, {T_DIR}, FORK, 800, FORK_STR, OCP_NO, CARRY_NO, 1},
	{"lld", TWO, {T_DIR | T_IND, T_REG}, LLD, 10, LLD_STR, OCP_YES, CARRY_YES, 0},
	{"lldi", THREE, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, LLDI, 50,
		LLDI_STR, OCP_YES, CARRY_YES, 1},
	{"lfork", ONE, {T_DIR}, LFORK, 1000, LFORK_STR, OCP_NO, CARRY_NO, 1},
	{"aff", ONE, {T_REG}, AFF, 2, AFF_STR, OCP_YES, CARRY_NO, 0},
	{0, ZERO, {0}, NA, 0, 0, OCP_NO, CARRY_NO, 0}
};
