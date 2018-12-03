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

void  name_and_comm(t_vm *vm, int i)
{
  int   i;
  char  *name;
  char  *comm;
  char  *bin;

  i = 0;
  bin = vm->player[i].bin;
  name = vm->player[i].name;
  comm = vm->player[i].comm;
  while (i < PROG_NAME_LENGTH)
  {
    name[i] = bin[i + 4];
    i++;
  }
  name[i] = 0;
  i = 0;
  while (i < COMMENT_LENGTH)
  {
    comm[i] = bin[i + 12 + PROG_NAME_LENGTH];
    i++;
  }
  comm[i] = 0;
}

/*
**parse function tries to parse each player's binary data to retrieve their
**information, i.e the [name], which is the name of the champion, the [comm],
**which will contain the commentary, and the [algo] containing the instructions.
*/

void  parse(t_vm *vm)
{
  int   i;

  i = 0;
  while (i < vm->nb_players)
  {
    name_and_comm(vm, i);
    //manque: check le nom, le comm, parse les instructions et check
    i++;
  }
}
