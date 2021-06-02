/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_octal_percent.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasuda <mmasuda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 14:55:41 by mmasuda           #+#    #+#             */
/*   Updated: 2021/06/01 17:05:20 by mmasuda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_octal(va_list vl, t_flag container)
{
	char			octal[256];
	size_t			ud;
	int				len;
	int				ret;

	len = 0;
	ud = (unsigned int)va_arg(vl, unsigned int);
	len = ft_convert_to_octal(&octal, ud, container, len);
	ret = len;
	ret = ft_branch_by_flag_hex(octal, ret, container, len);
	return (ret);
}

int	ft_convert_to_octal(char (*octal)[256], size_t n,
	t_flag container, int len)
{
	size_t	m;

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

int	ft_print_percent(t_flag container)
{
	int	ret;

	ret = 1;
	if (container.flags[0] == 1)
	{
		ft_putchar('%');
		while (container.width-- - 1 > 0)
			ret += ft_print_zero_or_space(container);
	}
	else
	{
		while (container.width-- - 1 > 0)
			ret += ft_print_zero_or_space(container);
		ft_putchar('%');
	}
	return (ret);
}
