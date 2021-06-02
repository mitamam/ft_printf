/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasuda <mmasuda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 14:53:15 by mmasuda           #+#    #+#             */
/*   Updated: 2021/06/01 12:16:22 by mmasuda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_int(va_list vl, t_flag container)
{
	long	d;
	int		digit;
	int		minus;
	int		ret;

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
		ret += ft_if_flag_0_is_1_int(d, digit, container, minus);
	else
		ret += ft_if_flag_0_is_0_int(d, digit, container, minus);
	return (ret);
}

int	ft_if_flag_0_is_1_int(long d, int digit, t_flag container, int minus)
{
	int	ret;

	if (d < 0)
	{
		ft_putchar('-');
		d *= -1;
	}
	ret = ft_print_prec(container, digit);
	if (d != 0 || container.precision != 0)
		ft_putnbr(d);
	ret += ft_print_width(container, digit, minus);
	return (ret);
}

int	ft_if_flag_0_is_0_int(long d, int digit, t_flag container, int minus)
{
	int	ret;

	if ((container.precision > container.width
			|| container.flags[1] == 1) && d < 0)
	{
		ft_putchar('-');
		d *= -1;
	}
	ret = ft_print_width(container, digit, minus);
	if (d < 0)
	{
		d *= -1;
		ft_putchar('-');
	}
	ret += ft_print_prec(container, digit);
	if (d != 0 || container.precision != 0)
		ft_putnbr(d);
	return (ret);
}

int	ft_count_digit(long d, int digit, int *minus, t_flag container)
{
	if (d == 0 && container.precision != 0)
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
