/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_name.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 21:53:31 by ldedier           #+#    #+#             */
/*   Updated: 2018/12/03 01:12:05 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int read_name_file(char *str, t_env *env) //toprotect
{
	int i;
	char *name;
	int index;

	i = 0;
	if (!str)
		return (1);
	while (str[i])
		i++;
	if (str[i - 1] != 's' || i == 0)
		return (1);
	index = 0;
	if (str[i - 1] == 's')
	{
		//i = 0;
		name = ft_strndup(&str[index], i - 2);
		env->champ.cor_name = ft_strjoin_free(name, ".cor");
		printf("name = %s\n", env->champ.cor_name);
		return (0);
	}
	return (0);
}
