/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasuda <mmasuda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 17:55:11 by mmasuda           #+#    #+#             */
/*   Updated: 2021/05/13 23:25:19 by mmasuda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		write(1, &str[i], 1);
		i++;
	}
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int	ft_strchr_idx(const char *s, int c)
{
	unsigned char	char_c;
	int				i;

	char_c = (char)c;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == char_c)
			return (i);
		i++;
	}
	return (-1);
}

int	ft_isdigit(int c)
{
	if ('0' <= c && c <= '9')
		return (1);
	return (0);
}

int	ft_find_flag(t_flag *container, const char *format, int idx)
{
	int flag_idx;

	flag_idx = 0;
	while (flag_idx >= 0)
	{
		if (format[idx] == '-')
			flag_idx = 0;
		else if (format[idx] == '0')
			flag_idx = 1;
		else if (format[idx] == ' ')
			flag_idx = 2;
		else
			flag_idx = -1;
		if (flag_idx >= 0)
		{
			container->flags[flag_idx] = 1;
			idx++;
		}
	}
	return (idx);
}

int	ft_store_width(t_flag *container, const char *format, int idx)
{
	while (('0' <= format[idx] && format[idx] <= '9')
		|| format[idx] == '*')
	{
		if (format[idx] == '*')
			container->width = -2;
		else
		{
			if (container->width == -1)
				container->width = 0;
			container->width *= 10;
			container->width += (int)format[idx] - '0';
		}
		idx++;
	}
	return (idx);
}

int	ft_store_prec(t_flag *container, const char *format, int idx)
{
	idx++;

	if (format[idx] != '*' && !('0' <= format[idx] && format[idx] <= '9'))
		container->precision = 0;
	if (format[idx] == '*')
	{
		container->precision = -2;
		idx++;
	}
	while ('0' <= format[idx] && format[idx] <= '9')
	{
		if (container->flags[1] == 1)
			container->flags[1] = 0;
		if (container->precision == -1)
			container->precision = 0;
		container->precision *= 10;
		container->precision += (int)format[idx] - '0';
		idx++;
	}
	return (idx);
}

void	ft_init_flag(t_flag *container)
{
	container->flags[0] = 0;
	container->flags[1] = 0;
	container->flags[2] = 0;
	container->width = -1;
	container->precision = -1;
	container->specifier = -1;
}

int	ft_find_spec(const char *format)
{
	if (*format == 'c')
		return (0);
	else if (*format == 's')
		return (1);
	else if (*format == 'p')
		return (2);
	else if (*format == 'd')
		return (3);
	else if (*format == 'i')
		return (4);
	else if (*format == 'u')
		return (5);
	else if (*format == 'x')
		return (6);
	else if (*format == 'X')
		return (7);
	else if (*format == 'o')
		return (8);
	else if (*format == '%')
		return (9);
	return (-1);
}

int	ft_store_to_container(const char *format, t_flag *container)
{
	int	idx;
	int	spec_idx;

	idx = 1;
	ft_init_flag(container);
	idx = ft_find_flag(container, format, idx);
	idx = ft_store_width(container, format, idx);
	if (format[idx] == '.')
		idx = ft_store_prec(container, format, idx);
	spec_idx = ft_find_spec(&format[idx]);
	if (spec_idx >= 0)
	{
		container->specifier = spec_idx;
		idx++;
	}
	return (idx);
}

void	ft_exists_asterisk(t_flag *container, va_list vl)
{
	if (container->width == -2)
	{
		container->width = (int)va_arg(vl, int);
		if (container->width < 0)
		{
			container->width *= -1;
			container->flags[0] = 1;
		}
	}
	if (container->precision == -2)
	{
		container->precision = (int)va_arg(vl, int);
		if (container->precision < 0)
			container->precision = -1;
	}
}

int	ft_print_char(va_list vl, t_flag container)
{
	unsigned char	c;
	int				ret;

	c = (unsigned char)va_arg(vl, int);
	ret = 1;
	if (container.flags[0] == 1)
	{
		write(1, &c, 1);
		while (container.width-- - 1 > 0)
		{
			ft_putchar(' ');
			ret++;
		}
	}
	else
	{
		while (container.width-- - 1 > 0)
		{
			ft_putchar(' ');
			ret++;
		}
		write(1, &c, 1);
	}
	return (ret);
}


int	ft_if_flag_0_is_0(t_flag container, int ret,
	char *s, int len)
{
	if (container.precision > len)
	{
		while (container.width-- - len > 0)
			ret += ft_print_zero_or_space(container);
		ft_putstr((char *)s);
		ret += len;
	}
	else
	{
		if (container.precision == 0)
			len = 0;
		else if (container.precision == -1)
			container.precision = len;
		ret = container.precision;
		while (container.width-- - container.precision > 0)
			ret += ft_print_zero_or_space(container);
		while (container.precision-- > 0 && *s != '\0')
			ft_putchar(*s++);
	}
	return (ret);
}

int	ft_if_flag_0_is_1(t_flag container, int ret, char *s, int len)
{
	if (container.precision > len)
	{
		ft_putstr((char *)s);
		while (container.width-- - len > 0)
			ret += ft_print_zero_or_space(container);
		ret += len;
	}
	else
	{
		if (container.precision == 0)
			len = 0;
		else if (container.precision == -1)
			container.precision = len;
		ret = container.precision;
		while (container.precision-- > 0 && *s != '\0')
			ft_putchar(*s++);
		container.precision = ret;
		while (container.width-- - container.precision > 0)
			ret += ft_print_zero_or_space(container);
	}
	return (ret);
}

int	ft_print_width_prec_char(t_flag container, int len, const char *s)
{
	int	ret;

	ret = 0;
	if (container.flags[0] == 1)
		ret = ft_if_flag_0_is_1(container, ret, (char *)s, len);
	else
		ret = ft_if_flag_0_is_0(container, ret, (char *)s, len);
	return (ret);
}

int	ft_print_char_ptr(va_list vl, t_flag container)
{
	const char	*s;
	int			ret;

	s = (const char *)va_arg(vl, const char *);
	if (s)
		ret = ft_print_width_prec_char(container, ft_strlen(s), s);
	else
	{
		s = "(null)";
		ret = ft_print_width_prec_char(container, 6, s);
	}
	return (ret);
}

int	ft_store_hex(unsigned char (*hex)[256], unsigned long n,
	t_flag container, int len)
{
	unsigned long	m;

	if (n == 0 && container.precision != 0)
	{
		(*hex)[len] = '0';
		len++;
	}
	while (n > 0)
	{
		m = n % 16;
		if (m < 10)
			(*hex)[len] = '0' + m;
		else
		{
			if (container.specifier == 7)
				(*hex)[len] = 'A' + (m % 10);
			else
				(*hex)[len] = 'a' + (m % 10);
		}
		len++;
		n /= 16;
	}
	(*hex)[len] = '\0';
	return (len);
}

void ft_put_hex(t_flag container, int len, unsigned char hex[256])
{
	if (container.specifier == 2)
	{
		ft_putstr("0x");
		len -= 2;
	}
	while (len-- > 0 && hex[len])
		ft_putchar(hex[len]);
}

int	ft_flag_0_0_or_1(unsigned char hex[256], int ret,
	t_flag container, int len)
{
	if (container.specifier == 2)
		len += 2;
	if (container.flags[0] == 1)
	{
		ret = ft_print_prec(container, len);
		ft_put_hex(container, len, hex);
		ret += ft_print_width(container, len, 0);
	}
	else
	{
		ret = ft_print_width(container, len, 0);
		ret += ft_print_prec(container, len);
		ft_put_hex(container, len, hex);
	}
	return (ret);
}

int	ft_print_hex(va_list vl, t_flag container)
{
	unsigned char	hex[256];
	unsigned long	n;
	int				ret;
	int				len;

	len = 0;
	n = (unsigned long)va_arg(vl, unsigned long);
	len = ft_store_hex(&hex, n, container, len);
	ret = len;
	ret = ft_flag_0_0_or_1(hex, ret, container, len);
	return (ret);
}

void	ft_putnbr(long nb)
{
	if (nb < 0)
	{
		ft_putchar('-');
		ft_putnbr(nb * (-1));
	}
	else if (nb > 9)
	{
		ft_putnbr(nb / 10);
		ft_putnbr(nb % 10);
	}
	else
		ft_putchar(nb + '0');
}

int	ft_count_digit(int d, int digit, int *minus, t_flag container)
{
	if (d == -2147483648)
	{
		digit = 10;
		*minus = 1;
	}
	else if (d == 0 && container.precision != 0)
		digit++;
	else if (d < 0)
	{
		d *= -1;
		*minus = 1;
	}
	while (d > 0)
	{
		d /= 10;
		digit++;
	}
	return (digit);
}

int	ft_print_zero_or_space(t_flag container)
{
	if (container.flags[1] == 1 && container.flags[0] != 1)
		ft_putchar('0');
	else
		ft_putchar(' ');
	return (1);
}

int	ft_print_width(t_flag container, int digit, int minus)
{
	int	ret;

	ret = digit;
	if (container.precision > digit)
	{
		ret = container.precision;
		while (container.width-- - container.precision - minus > 0)
			ret += ft_print_zero_or_space(container);
	}
	else
	{
		while (container.width-- - digit - minus > 0)
			ret += ft_print_zero_or_space(container);
	}
	return (ret + minus);
}

int	ft_print_prec(t_flag container, int digit)
{
	int	ret;

	ret = 0;
	if (container.precision > digit)
	{
		while (container.precision-- - digit)
			ft_putchar('0');
	}
	return (ret);
}

int	ft_print_int(va_list vl, t_flag container)
{
	int	d;
	int	digit;
	int	minus;
	int	ret;

	digit = 0;
	minus = 0;
	ret = 0;
	d = (int)va_arg(vl, int);
	digit = ft_count_digit(d, digit, &minus, container);
	if (container.flags[2] == 1)
	{
		ft_putchar(' ');
		ret++;
	}
	if (container.flags[0] == 1)
	{
		if (d < 0 && d != -2147483648)
		{
			ft_putchar('-');
			d *= -1;
		}
		ret += ft_print_prec(container, digit);
		if (d != 0 || container.precision != 0)
			ft_putnbr(d);
		ret += ft_print_width(container, digit, minus);
	}
	else
	{
		if ((container.precision > container.width || container.flags[1] == 1) && minus)
		{
			ft_putchar('-');
			d *= -1;
		}
		ret += ft_print_width(container, digit, minus);
		if (minus && d != -2147483648 && d < 0)
		{
			d *= -1;
			ft_putchar('-');
		}
		ret += ft_print_prec(container, digit);
		if (d != 0 || container.precision != 0)
			ft_putnbr(d);
	}
	return (ret);
}

int	ft_print_unsigned_int(va_list vl, t_flag container)
{
	unsigned int	ud;
	unsigned int	ud_tmp;
	int				ret;
	int				digit;

	ud = (unsigned int)va_arg(vl, unsigned int);
	ud_tmp = ud;
	digit = 0;
	ret = 0;
	if (ud_tmp == 0 && container.precision != 0)
		digit++;
	while (ud_tmp > 0)
	{
		ud_tmp /= 10;
		digit++;
	}
	if (container.flags[0] == 1)
	{
		ret = ft_print_prec(container, digit);
		if (ud != 0 || container.precision != 0)
			ft_putnbr(ud);
		ret += ft_print_width(container, digit, 0);
	}
	else
	{
		ret = ft_print_width(container, digit, 0);
		ret += ft_print_prec(container, digit);
		if (ud != 0 || container.precision != 0)
			ft_putnbr(ud);
	}
	return (ret);
}

int	ft_store_octal(unsigned char (*octal)[256], unsigned int n,
	t_flag container, int len)
{
	unsigned long	m;

	if (n == 0 && container.precision != 0)
	{
		(*octal)[len] = '0';
		len++;
	}
	while (n > 0)
	{
		m = n % 8;
		if (m < 10)
			(*octal)[len] = '0' + m;
		len++;
		n /= 8;
	}
	(*octal)[len] = '\0';
	return (len);
}

int	ft_print_octal(va_list vl, t_flag container)
{
	unsigned char	octal[256];
	unsigned int	ud;
	int				len;
	int				ret;

	len = 0;
	ud = (unsigned int)va_arg(vl, unsigned int);
	len = ft_store_octal(&octal, ud, container, len);
	ret = len;
	ret = ft_flag_0_0_or_1(octal, ret, container, len);
	return (ret);
}

int	ft_print_percent(t_flag container)
{
	int	ret;

	ret = 1;
	if (container.flags[0] == 1)
	{
		ft_putchar('%');
		ft_print_prec(container, 1);
		while (container.width-- - 1 > 0)
			ret += ft_print_zero_or_space(container);
	}
	else
	{
		while (container.width-- - 1 > 0)
			ret += ft_print_zero_or_space(container);
		ft_print_prec(container, 1);
		ft_putchar('%');
	}
	return (ret);
}

int	ft_print_format(t_flag container, va_list vl)
{
	int ret;

	ret = 1;
	ft_exists_asterisk(&container, vl);
	if (container.specifier == 0)
		ret = ft_print_char(vl, container);
	else if (container.specifier == 1)
		ret = ft_print_char_ptr(vl, container);
	else if (container.specifier == 2 || container.specifier == 6
		|| container.specifier == 7)
		ret = ft_print_hex(vl, container);
	else if (container.specifier == 3 || container.specifier == 4)
		ret = ft_print_int(vl, container);
	else if (container.specifier == 5)
		ret = ft_print_unsigned_int(vl, container);
	else if (container.specifier == 8)
		ret = ft_print_octal(vl, container);
	else if (container.specifier == 9)
		ret = ft_print_percent(container);
	else
		return (-1);
	return (ret);
}

int	ft_print_str(const char *format, int *print_len)
{
	int	i;
	int	chr_idx;

	i = 0;
	if (ft_strchr_idx(format, '%') != -1)
		chr_idx = ft_strchr_idx(format, '%');
	else
		chr_idx = ft_strlen(format);
	while (i < chr_idx)
	{
		write(1, &format[i], 1);
		i++;
	}
	*print_len += (chr_idx);
	return (chr_idx);
}

int	ft_printf(const char *format, ...)
{
	t_flag container;
	va_list vl;
	int i;
	int ret;

	i = 0;
	ret = 0;
	va_start(vl, format);
	if (!format)
		i = -1;
	while (i >= 0 && format[i] != '\0')
	{
		if (format[i] == '%')
		{
			i += ft_store_to_container(&format[i], &container);
			ret += ft_print_format(container, vl);
		}
		else
			i += ft_print_str(&format[i], &ret);
	}
	va_end(vl);
	return (ret);
}