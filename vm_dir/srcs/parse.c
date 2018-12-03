/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uboumedj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 15:40:17 by uboumedj          #+#    #+#             */
/*   Updated: 2018/11/31 17:46:43 by uboumedj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

/*
**name_and_comm static function is used by the parse function to save
**the name and the comment of given files into their respective arrays in each
**player's structure: player[x].name and player[x].comm
*/

static void   name_and_comm(t_vm *vm, int i)
{
  int   n;
  char  *name;
  char  *comm;
  char  *bin;

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
**check_name_comm static function is used by the parse function to check the
**name and comm arrays of the given player to make sure it contains no forbi-
**den characters
*/

static void   check_name_comm(t_vm *vm, int i)
{
  char  *name;
  char  *comm;
  int   n;

  name = vm->player[i].name;
  comm = vm->player[i].comm;
  n = 0;
  while (name[n] != 0)
  {
    if (!(ft_strchr(LABEL_CHARS, name[n])))
      error_exit(11);
    n++;
  }
  n = 0;
  while (comm[n] != 0)
  {
    if (!(ft_strchr(LABEL_CHARS, comm[n])))
      error_exit(12);
    n++;
  }
}

/*
**instructions static function is used by the parse function to add the [algo]
**part (the instructions) inside the player structure. It also checks if the
**instructions part exceeds the max allowed size CHAMP_MAX_SIZE.
*/

static void   instructions(t_vm *vm, int i)
{
  char  *algo;
  char  *bin;
  int   n;

  algo = vm->player[i].algo;
  bin = vm->player[i].bin;
  n = 0;
  while (PROG_NAME_LENGTH + 16 + COMMENT_LENGTH + n < vm->player[i].file_len)
  {
    algo[n] = bin[PROG_NAME_LENGTH + 16 + COMMENT_LENGTH + n];
    n++;
  }
  if (n > CHAMP_MAX_SIZE)
    error_exit2(1);
}

/*
**parse function tries to parse each player's binary data to retrieve their
**information, i.e the [name], which is the name of the champion, the [comm],
**which will contain the commentary, and the [algo] containing the instructions.
*/

void          parse(t_vm *vm)
{
  int   i;

  i = 0;
  while (i < vm->nb_players)
  {
    name_and_comm(vm, i);
    check_name_comm(vm, i);
    instructions(vm, i);
    i++;
  }
}
