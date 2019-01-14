#include "asm.h"

int		ft_describe_label(char *str, int n, t_env *e)
{
	int i;

	i = 0;
	if (n == 0)
	{
		ft_log_error(LEXICAL_ERROR, 0, e);
		return (0);
	}
	while (str[i] && i < n)
	{
		if (!ft_is_in_str(LABEL_CHARS, str[i]))
		{
			ft_log_error(LEXICAL_ERROR, i, e);
			return (0);
		}
		i++;
	}
	return (1);
}

int		ft_fill_instructions_labels_values(t_env *e)
{
	t_list			*ptr;
	t_instruction	*instruction;
	int				i;

	ptr = e->champ.instructions;
	while (ptr != NULL)
	{
		instruction = (t_instruction *)(ptr->content);
		i = 0;
		while (i < instruction->op.nb_params)
		{
			if (instruction->params[i].type & T_LAB)
			{
				if (ft_process_fill_instruction_label_value(instruction,
							i, e->champ.labels))
					return (ft_log_no_label_error(instruction,
								i, e));
			}
			i++;
		}
		ptr = ptr->next;
	}
	return (0);
}


t_label		*ft_new_label(char *name, int address)
{
	t_label	*label;

	if (!(label = (t_label *)(malloc(sizeof(t_label)))))
		return (NULL);
	label->name = name;
	label->address = address;
	return (label);
}

t_label	*ft_get_label(t_list *labels, char *label_name)
{
	t_list *ptr;
	t_label *label;

	ptr = labels;
	while (ptr != NULL)
	{
		label = (t_label *)(ptr->content);
		if (!ft_strcmp(label->name, label_name))
			return (label);
		ptr = ptr->next;
	}
	return (NULL);
}

int		ft_add_new_label(char *str, int length, t_env *e)
{
	t_label	*label;
	char	*label_name;

	if (!(label_name = ft_strndup(str, length)))
		return (ft_log_error(MALLOC_ERROR, 0, e));
	if (ft_get_label(e->champ.labels, label_name))
	{
		free(label_name);
		return (ft_log_error(EXISTS_LABEL, 0, e));
	}
	if (!(label = ft_new_label(label_name, e->champ.header.prog_size)))
	{
		free(label_name);
		return (ft_log_error(MALLOC_ERROR, 0, e));
	}
	if (ft_add_to_list_ptr_back(&(e->champ.labels), label, sizeof(t_label)))
	{
		ft_free_label(label);
		return (ft_log_error(MALLOC_ERROR, 0, e));
	}
	e->parser.column_offset += length + 1;
	return (0);
}
