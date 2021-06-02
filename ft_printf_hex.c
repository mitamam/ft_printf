/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasuda <mmasuda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 14:36:11 by mmasuda           #+#    #+#             */
/*   Updated: 2021/06/01 11:12:44 by mmasuda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_hex(va_list vl, t_flag container)
{
	char			hex[256];
	size_t			n;
	int				ret;
	int				len;

	len = 0;
	if (container.specifier == 2)
		n = (size_t)va_arg(vl, size_t);
	else
		n = (unsigned int)va_arg(vl, unsigned int);
	len = ft_convert_to_hex(&hex, n, container, len);
	ret = len;
	ret = ft_branch_by_flag_hex(hex, ret, container, len);
	return (ret);
}

int	ft_convert_to_hex(char (*hex)[256], size_t n,
	t_flag container, int len)
{
	size_t	m;

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

void	ft_put_hex(t_flag container, int len, char hex[256])
{
	if (container.specifier == 2 && container.precision == -1
		&& container.width != -1)
		ft_putstr("0x");
	while (len-- > 0 && hex[len])
		ft_putchar(hex[len]);
}

int	ft_branch_by_flag_hex(char hex[256], int ret,
	t_flag container, int len)
{
	int	memaddr_len;

	memaddr_len = 0;
	if (container.specifier == 2)
		memaddr_len = 2;
	if (container.flags[0] == 1)
	{
		if (container.specifier == 2
			&& (container.precision != -1 || container.width == -1))
			ft_putstr("0x");
		ret = ft_print_prec(container, len);
		ft_put_hex(container, len, hex);
		ret += ft_print_width(container, len + memaddr_len, 0);
	}
	else
	{
		ret = ft_print_width(container, len + memaddr_len, 0);
		if (container.specifier == 2
			&& (container.precision != -1 || container.width == -1))
			ft_putstr("0x");
		ret += ft_print_prec(container, len);
		ft_put_hex(container, len, hex);
	}
	ret += ft_increase_variable_ret(container);
	return (ret);
}

int	ft_increase_variable_ret(t_flag container)
{
	if (container.specifier == 2
		&& container.width < container.precision && container.precision != 0)
		return (2);
	return (0);
}
