/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 17:44:16 by ldedier           #+#    #+#             */
/*   Updated: 2018/11/30 20:15:45 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int read_name_file(char *str, t_env *env)
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
		env->champ.file_name = ft_strjoin(name, ".cor");
		printf("name = %s\n", name);
		printf("name = %s\n", env->champ.file_name);
		return (0);
	}
	return (0);
}

void	ft_init_env(t_env *e)
{
	e->parser.nb_line = 0;
	e->parser.parsed_name = 0;
	e->parser.parsed_comment = 0;
	e->champ.instructions = NULL;
}

int ft_print_usage(char *progname)
{
	ft_dprintf(2, "Usage: %s <sourcefile.s>\n", progname);
	return (1);
}

int main(int argc, char **argv)
{
	t_env env;

	(void)argc;
	ft_init_env(&env);
	if (argc != 2)
		return (ft_print_usage(argv[0]));
	if ((read_name_file(argv[1], &env)) == 1)
	{
		ft_printf("Source file wrong syntax\n");
		return (0);
	}
	if (ft_parse_asm(argv[1], &env))
		ft_printf("error.. qqch\n");
	return (0);
}
