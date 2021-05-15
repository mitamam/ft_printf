/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasuda <mmasuda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 10:17:46 by mmasuda           #+#    #+#             */
/*   Updated: 2021/05/13 23:27:48 by mmasuda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	FT_PRINTF_H
# define	FT_PRINTF_H

#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct	s_flag
{
	int flags[3];
	int width;
	int precision;
	int specifier;
}				t_flag;

int		ft_print_format(t_flag container, va_list vl);
int		ft_print_str(const char *format, int *print_len);
int		ft_printf(const char *format, ...);
void	ft_init_flag(t_flag *container);

int		ft_store_to_container(const char *format, t_flag *container);
int		ft_store_width(t_flag *container, const char *format, int idx);
int		ft_store_prec(t_flag *container, const char *format, int idx);
int		ft_find_flag(t_flag *container, const char *format, int idx);
int		ft_find_spec(const char *format);
void	ft_exists_asterisk(t_flag *container, va_list vl);

int		ft_print_char(va_list vl, t_flag container);
int		ft_if_flag_0_is_0(t_flag container, int ret, char *s, int len);
int		ft_if_flag_0_is_1(t_flag container, int ret,
	char *s, int len);
int		ft_print_width_prec_char(t_flag container, int len, const char *s);
int		ft_print_char_ptr(va_list vl, t_flag container);

int		ft_store_hex(unsigned char (*hex)[256], unsigned long n,
	t_flag container, int len);
int		ft_print_hex(va_list vl, t_flag container);
int		ft_flag_0_0_or_1(unsigned char hex[256], int ret,
	t_flag container, int len);

void	ft_putnbr(long nb);
int		ft_count_digit(int d, int digit, int *minus, t_flag container);
int		ft_print_zero_or_space(t_flag container);

int		ft_print_width(t_flag container, int digit, int minus);
int		ft_print_prec(t_flag container, int digit);
int		ft_print_int(va_list vl, t_flag container);
int		ft_print_unsigned_int(va_list vl, t_flag container);

int		ft_print_octal(va_list vl, t_flag container);
int		ft_store_octal(unsigned char (*octal)[256], unsigned int n,
	t_flag container, int len);

int		ft_print_percent(t_flag container);

void	ft_putchar(char c);
void	ft_putstr(char *str);
size_t	ft_strlen(const char *s);
int		ft_strchr_idx(const char *s, int c);
int		ft_isdigit(int c);

#endif