/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasuda <mmasuda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 14:28:27 by mmasuda           #+#    #+#             */
/*   Updated: 2021/05/31 15:41:18 by mmasuda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_find_flag(t_flag *container, const char *format, int idx)
{
	int	flag_idx;

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

int	ft_store_precision(t_flag *container, const char *format, int idx)
{
	idx++;
	container->precision = 0;
	if (format[idx] == '*')
	{
		container->precision = -2;
		idx++;
	}
	while ('0' <= format[idx] && format[idx] <= '9')
	{
		container->precision *= 10;
		container->precision += (int)format[idx] - '0';
		idx++;
	}
	return (idx);
}

int	ft_find_specifier(const char *format)
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

void	ft_init_flag(t_flag *container)
{
	container->flags[0] = 0;
	container->flags[1] = 0;
	container->flags[2] = 0;
	container->width = -1;
	container->precision = -1;
	container->specifier = -1;
}
