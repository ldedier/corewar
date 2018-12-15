/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 20:42:40 by emuckens          #+#    #+#             */
/*   Updated: 2018/12/15 20:55:25 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"

void		color_off(void)
{
	ft_printf("%s", COLF_OFF);
}
void	*get_color_ptr(char index)
{
	static t_color_type color[NB_COLORS] = {
		{COL_BLACK, COLF_BLACK},
		{COL_RED, COLF_RED},
		{COL_GREEN, COLF_GREEN},
		{COL_BROWN, COLF_BROWN},
		{COL_BLUE, COLF_BLUE},
		{COL_MAGENTA, COLF_MAGENTA},
		{COL_CYAN, COLF_CYAN},
		{COL_GREY, COLF_GREY}, 
		{COL_BBLACK, COLF_BBLACK},
		{COL_BRED, COLF_BRED},
		{COL_BGREEN, COLF_BGREEN},
		{COL_BBROWN, COLF_BBROWN},
		{COL_BBLUE, COLF_BBLUE},
		{COL_BMAGENTA, COLF_BMAGENTA},
		{COL_BCYAN, COLF_BCYAN},
		{COL_BGREY, COLF_BGREY},
		{COL_OFF, COLF_OFF}};
	return ((void *)&color[(int)index]);
}


void		color_on_term(char index)
{
	ft_printf("%s", (char *)(get_color_ptr(index) + sizeof(int)));
}

int			get_color_sdl(char index)
{
	return (*(int *)get_color_ptr(index));
}

void		set_color(t_player *player, char *color_index_ref, char index)
{
	player->color.index = index;
	player->color.value = get_color_ptr(color_index_ref[(int)index]);
}

char	*init_color_ref(char **env)
{
	char	***env_var;
	static char	color_ref_index[MAX_PL_COLOR];
	int	i;
	int	nb_envar;
	int index;

	if (!color_ref_index[2])
	{	
		nb_envar = get_envar(env, &env_var);
		if ((index = get_envar_index(env_var, COREWAR_VAR_NAME, nb_envar)) != -1)
			ft_strlcat(color_ref_index, env_var[(int)index][1], MAX_PL_COLOR);
		else
			ft_strlcat(color_ref_index, DEFAULT_COLORS, MAX_PL_COLOR);
		i = -1;
		while (color_ref_index[++i])
		{
			color_ref_index[i] = (char)ft_strichr(COL_DESIGNATOR, color_ref_index[i]);
		}
	}
	return (color_ref_index);
}
