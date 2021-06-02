/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasuda <mmasuda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 10:17:46 by mmasuda           #+#    #+#             */
/*   Updated: 2021/06/01 17:03:33 by mmasuda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_flag
{
	int	flags[3];
	int	width;
	int	precision;
	int	specifier;
}				t_flag;

int		ft_printf(const char *format, ...);
int		ft_store_to_container(const char *format, t_flag *container);
int		ft_print_format(t_flag container, va_list vl);
int		ft_print_str(const char *format, int *ret);

int		ft_find_specifier(const char *format);
int		ft_store_width(t_flag *container, const char *format, int idx);
int		ft_store_precision(t_flag *container, const char *format, int idx);
int		ft_find_flag(t_flag *container, const char *format, int idx);
void	ft_init_flag(t_flag *container);

void	ft_exists_asterisk(t_flag *container, va_list vl);
int		ft_print_zero_or_space(t_flag container);
int		ft_print_width(t_flag container, int digit, int minus);
int		ft_print_prec(t_flag container, int digit);

int		ft_print_int(va_list vl, t_flag container);
int		ft_if_flag_0_is_1_int(long d, int digit, t_flag container, int minus);
int		ft_if_flag_0_is_0_int(long d, int digit, t_flag container, int minus);
int		ft_count_digit(long d, int digit, int *minus, t_flag container);
void	ft_putnbr(long nb);

int		ft_print_unsigned_int(va_list vl, t_flag container);

int		ft_print_char(va_list vl, t_flag container);
int		ft_print_char_ptr(va_list vl, t_flag container);
int		ft_branch_by_flag_char(t_flag container, int len, const char *s);
int		ft_if_flag_0_is_0_char(t_flag container, int ret,
			char *s, int len);
int		ft_if_flag_0_is_1_char(t_flag container, int ret, char *s, int len);

int		ft_print_hex(va_list vl, t_flag container);
int		ft_convert_to_hex(char (*hex)[256], size_t n,
			t_flag container, int len);
int		ft_branch_by_flag_hex(char hex[256], int ret,
			t_flag container, int len);
void	ft_put_hex(t_flag container, int len, char hex[256]);
int		ft_increase_variable_ret(t_flag container);

int		ft_convert_to_octal(char (*octal)[256], size_t n,
			t_flag container, int len);
int		ft_print_octal(va_list vl, t_flag container);
int		ft_print_percent(t_flag container);

void	ft_putchar(char c);
void	ft_putstr(char *str);
size_t	ft_strlen(const char *s);
int		ft_strchr_idx(const char *s, int c);
int		ft_isdigit(int c);

#endif
