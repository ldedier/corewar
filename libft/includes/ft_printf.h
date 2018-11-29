/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/07 01:13:42 by ldedier           #+#    #+#             */
/*   Updated: 2018/06/12 10:49:02 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

# define NB_CHARS	255
# define BUF_SIZE	1000000

# define RED		"\x1B[31m"
# define GREEN 		"\x1B[32m"
# define YELLOW		"\x1B[33m"
# define BLUE		"\x1B[34m"
# define MAGENTA	"\x1B[35m"
# define CYAN		"\x1B[36m"
# define WHITE		"\x1B[37m"
# define L_GREY		"\x1B[90m"
# define L_BLUE		"\x1B[94m"
# define L_MAGENTA	"\x1B[95m"
# define L_CYAN		"\x1B[96m"

# define BRED		"\x1B[41m"
# define BGREEN 	"\x1B[42m"
# define BYELLOW	"\x1B[43m"
# define BBLUE		"\x1B[44m"
# define BMAGENTA	"\x1B[44m"
# define BCYAN		"\x1B[46m"
# define BWHITE		"\x1B[47m"
# define BL_BLUE	"\x1B[104m"
# define BL_MAGENTA	"\x1B[105m"
# define BL_CYAN	"\x1B[106m"

# define BOLD		"\x1b[1m"
# define UNDERLINE	"\x1b[4m"

# define EOC		"\033[0m"

typedef union		u_var
{
	intmax_t		integer;
	double			flottant;
	char			*str;
	int				*wstr;
}					t_var_union;

/*
** defines the kind of padding the display has to use
*/
typedef enum		e_padding
{
	e_padding_standard,
	e_padding_zeros,
	e_padding_negative
}					t_padding;

/*
** defines the behaviour with positive numbers
*/
typedef enum		e_prefix
{
	e_prefix_none,
	e_prefix_blank,
	e_prefix_plus
}					t_prefix;

/*
** defines the length modification flag
*/
typedef enum		e_length_mod
{
	e_mod_none,
	e_mod_signed_char,
	e_mod_short_int,
	e_mod_size_t,
	e_mod_long_int,
	e_mod_long_long_int,
	e_mod_intmax_t
}					t_length_mod;

/*
** gather the different flags to take in account to the display
*/
typedef struct		s_flags
{
	t_padding		padding_style;
	t_prefix		prefix;
	t_length_mod	length_mod;
	int				display_style;
	int				padding;
	int				precision;
}					t_flags;

typedef struct		s_pf
{
	t_var_union		var;
	t_flags			flags;
	int				parse_precision;
	int				parse_padding;
	int				precised_precision;
	char			*buffer;
	int				fd;
	int				sprintf;
}					t_pf;

typedef int			(*t_pf_func)(t_pf *, va_list, char);
typedef void		(*t_get_val)(t_pf *, va_list);

int					ft_printf(const char *restrict format, ...);
int					ft_dprintf(int fd, const char *restrict format, ...);
int					ft_sprintf(char *buff, const char *restrict format, ...);
int					ft_dvprintf(int fd, const char *restrict ft, va_list va);
void				ft_init_pf(t_pf *pf);
int					ft_add_return(int n);
int					ft_reset_return(void);
int					ft_pf_0(t_pf *pf, va_list va, char c);
int					ft_pf_d(t_pf *pf, va_list va, char c);
int					ft_pf_d_maj(t_pf *pf, va_list va, char c);
int					ft_pf_s(t_pf *pf, va_list va, char c);
int					ft_pf_s_maj(t_pf *pf, va_list va, char c);
int					ft_pf_x(t_pf *pf, va_list va, char c);
int					ft_pf_x_maj(t_pf *pf, va_list va, char c);
int					ft_pf_o(t_pf *pf, va_list va, char c);
int					ft_pf_o_maj(t_pf *pf, va_list va, char c);
int					ft_pf_c(t_pf *pf, va_list va, char c);
int					ft_pf_c_maj(t_pf *pf, va_list va, char c);
int					ft_pf_u(t_pf *pf, va_list va, char c);
int					ft_pf_u_maj(t_pf *pf, va_list va, char c);
int					ft_pf_p(t_pf *pf, va_list va, char c);

int					ft_pf_h(t_pf *pf, va_list va, char c);
int					ft_pf_l(t_pf *pf, va_list va, char c);
int					ft_pf_j(t_pf *pf, va_list va, char c);
int					ft_pf_z(t_pf *pf, va_list va, char c);

int					ft_pf_f(t_pf *pf, va_list va, char c);
int					ft_pf_n(t_pf *pf, va_list va, char c);
int					ft_pf_nothing(t_pf *pf, va_list va, char c);

int					ft_pf_r(t_pf *pf, va_list va, char c);
int					ft_pf_b(t_pf *pf, va_list va, char c);

int					ft_pf_point(t_pf *pf, va_list va, char c);
int					ft_pf_hashtag(t_pf *pf, va_list va, char c);
int					ft_pf_minus(t_pf *pf, va_list va, char c);
int					ft_pf_plus(t_pf *pf, va_list va, char c);
int					ft_pf_space(t_pf *pf, va_list va, char c);
int					ft_pf_percent(t_pf *pf, va_list va, char c);
int					ft_pf_star(t_pf *pf, va_list va, char c);
int					ft_pf_digit(t_pf *pf, va_list va, char c);

int					ft_pf_len_d(t_pf pf);
int					ft_pf_len_u(t_pf pf);
int					ft_pf_len_s(t_pf pf);
int					ft_pf_len_s_maj(t_pf pf);
int					ft_wchar_len(int nb);
int					ft_wstrlen(int *data);
int					ft_pf_len_p(t_pf pf);
int					ft_pf_len_o(t_pf pf);
int					ft_pf_len_b(t_pf pf);
int					ft_pf_len_o_maj(t_pf pf);
int					ft_pf_len_x(t_pf pf);

int					ft_max(int a, int b);
void				ft_bzero(void *s, size_t n);
size_t				ft_strlen(char const *s);
char				*ft_strncpy(char *dest, char const *src, size_t n);
int					ft_isprint(int c);
void				ft_putchar_buff(char c, t_pf *pf);
void				ft_putbin(size_t nb, t_pf *pf);
void				ft_putdbl(double d, int precision, t_pf *pf);
void				ft_putnbr_buff(int nbr, t_pf *pf);
void				ft_putnbr_unsigned(unsigned int n, t_pf *pf);
void				ft_putnbr_max(uintmax_t n, t_pf *pf);
void				ft_putstr_non_printable(const char *s, size_t n, t_pf *pf);
intmax_t			ft_abs_max(intmax_t a);
void				ft_putnstr(char const *str, size_t n, t_pf *pf);
double				ft_fabs(double a);
int					ft_min(int a, int b);
int					ft_max(int a, int b);

void				ft_gtvar_none(t_pf *pf, va_list va);
void				ft_gtvar_signed_char(t_pf *pf, va_list va);
void				ft_gtvar_short_int(t_pf *pf, va_list va);
void				ft_gtvar_size_t(t_pf *pf, va_list va);
void				ft_gtvar_long_int(t_pf *pf, va_list va);
void				ft_gtvar_long_long_int(t_pf *pf, va_list va);
void				ft_gtvar_intmax_t(t_pf *pf, va_list va);
void				ft_gtvar_uint(t_pf *pf, va_list va);
void				ft_gtvar_uchar(t_pf *pf, va_list va);
void				ft_gtvar_ulint(t_pf *pf, va_list va);
void				ft_gtvar_ullint(t_pf *pf, va_list va);
void				ft_gtvar_uintmax_t(t_pf *pf, va_list va);
void				ft_gtvar_ushort_int(t_pf *pf, va_list va);

void				ft_puthex_max(uintmax_t n, int maj, t_pf *pf);
void				ft_putoctal_max(uintmax_t n, t_pf *pf);
char				*ft_get_buffer(const void *s, size_t n, int *disp, t_pf *p);
void				ft_empty_buffer(t_pf *pf);
void				ft_no_number(t_pf *pf);
void				get_casted_value(t_pf *pf, va_list va);
void				get_casted_value_unsigned(t_pf *pf, va_list va);
void				get_casted_value_unsigned_maj(t_pf *pf, va_list va);
void				ft_add_padding_pre(t_pf *pf, int no_padding_byte);
void				ft_add_padding_post(t_pf *pf, int no_padding_byte);
void				ft_add_padding_pre_standard(t_pf *pf, int no_padding_byte);
void				ft_add_padding_pre_zeros(t_pf *pf, int no_padding_byte);
void				ft_add_precision_base(t_pf *pf, int base);
void				ft_add_precision_o(t_pf *pf);
void				ft_add_precision_base_u(t_pf *pf, int base);
void				ft_add_prefix(t_pf *pf);
int					ft_put_wchar(int value, t_pf *pf);
void				ft_putwstr(int *data, t_pf *pf);
void				ft_putwnstr(int *data, int precision, t_pf *pf);
void				ft_4_bytes_len(unsigned char str[4], int value);
void				ft_3_bytes_len(unsigned char str[4], int value);
int					ft_wstrlen(int *data);
int					ft_wstrlen_prec(int *data, int precision);
int					ft_has_forbidden_values(t_pf pf);
int					ft_may_error_next_conv(const char *format, int i);
int					ft_process_percent(const char *f,
					int *i, t_pf *fg, va_list v);
#endif
