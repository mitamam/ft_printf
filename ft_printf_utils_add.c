/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_add.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasuda <mmasuda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 14:31:01 by mmasuda           #+#    #+#             */
/*   Updated: 2021/06/01 16:25:12 by mmasuda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
	if ((container->specifier >= 3 && container->specifier <= 8)
		&& container->precision != -1)
		container->flags[1] = 0;
}

int	ft_print_zero_or_space(t_flag container)
{
	if (container.flags[1] == 1 && container.flags[0] == 0)
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
