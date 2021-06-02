/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_unsigned_int.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasuda <mmasuda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 14:54:37 by mmasuda           #+#    #+#             */
/*   Updated: 2021/06/01 17:04:53 by mmasuda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_unsigned_int(va_list vl, t_flag container)
{
	size_t			ud;
	int				ret;
	int				digit;

	ud = (unsigned int)va_arg(vl, unsigned int);
	ret = 0;
	digit = 0;
	digit = ft_count_digit(ud, digit, 0, container);
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
