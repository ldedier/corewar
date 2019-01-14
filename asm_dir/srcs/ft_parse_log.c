#include "asm.h"

int		ft_log_custom_nb_params_error(int offset, t_env *e)
{
	char *str;
	char *nb_instructions;

	if (!(str = ft_strdup(e->parser.current_instruction->op.instruction_name)))
		return (ft_log_error(MALLOC_ERROR, 0, e));
	if (!(str = ft_strjoin_free(str, " instruction takes exactly ")))
		return (ft_log_error(MALLOC_ERROR, 0, e));
	if (!(nb_instructions =
				ft_itoa(e->parser.current_instruction->op.nb_params)))
	{
		free(str);
		return (ft_log_error(MALLOC_ERROR, 0, e));
	}
	if (!(str = ft_strjoin_free(str, nb_instructions)))
	{
		free(nb_instructions);
		return (ft_log_error(MALLOC_ERROR, 0, e));
	}
	free(nb_instructions);
	if (!(str = ft_strjoin_free(str,
					e->parser.current_instruction->op.nb_params == 1 ?
					" argument !" : " arguments !")))
		return (ft_log_error(MALLOC_ERROR, 0, e));
	return (ft_log_error(str, offset, e));
}

int		ft_log_custom_wrong_param_type(char *arg_type, int index, int offset,
			t_env *e)
{
	char *str;
	char *index_str;

	if (!(str = ft_strdup(e->parser.current_instruction->op.instruction_name)))
		return (ft_log_error(MALLOC_ERROR, 0, e));
	if (!(str = ft_strjoin_free(str, "'s parameter #")))
		return (ft_log_error(MALLOC_ERROR, 0, e));
	if (!(index_str = ft_itoa(index + 1)))
	{
		free(str);
		return (ft_log_error(MALLOC_ERROR, 0, e));
	}
	if (!(str = ft_strjoin_free(str, index_str)))
	{
		free(index_str);
		return (ft_log_error(MALLOC_ERROR, 0, e));
	}
	free(index_str);
	if (!(str = ft_strjoin_free(str, " can not be of type ")))
		return (ft_log_error(MALLOC_ERROR, 0, e));
	if (!(str = ft_strjoin_free(str, arg_type)))
		return (ft_log_error(MALLOC_ERROR, 0, e));
	return (ft_log_error(str, offset, e));
}
