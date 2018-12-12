#include "op.h"


void	color_off(void)
{
	ft_printf("%s%s", COLF_OFF, COLB_OFF);
}

void	color_on(t_color *c, int index)
{
	static char col_fg[NB_COLORS] = {COLF_BLACK, COLF_RED, COLF_GREEN, COLF_BROWN, COLF_BLUE, COLF_MAGENTA, COLF_CYAN, COLF_GREY};
	static char col_bg[NB_COLORS] = {COLB_BLACK, COLB_RED, COLB_GREEN, COLB_BROWN, COLB_BLUE, COLB_MAGENTA, COLB_CYAN, COLB_GREY};
	
	ft_printf("%s%s", col_fg[color.ref[index * 2]], col_bg[color.ref[index * 2] + 1]);
}

void	set_colors(t_vm *vm, int index)
{
	int		index;
	char *color_ref = "pspcplpdpvrlrarrtmtctep0p1p2p3p4p5p6p7p8p9";
	
	index = -1;
	while(++index)
		color_ref[index] = ft_strchri(COL_DESIGNATOR, str[index]);
}
