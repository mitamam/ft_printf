/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasuda <mmasuda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 17:55:11 by mmasuda           #+#    #+#             */
/*   Updated: 2021/05/31 15:41:26 by mmasuda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_store_to_container(const char *format, t_flag *container)
{
	int	idx;
	int	spec_idx;

	idx = 1;
	ft_init_flag(container);
	idx = ft_find_flag(container, format, idx);
	idx = ft_store_width(container, format, idx);
	if (format[idx] == '.')
		idx = ft_store_precision(container, format, idx);
	spec_idx = ft_find_specifier(&format[idx]);
	if (spec_idx >= 0)
	{
		container->specifier = spec_idx;
		idx++;
	}
	return (idx);
}

int	ft_print_format(t_flag container, va_list vl)
{
	int	ret;

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
		ret = -1;
	return (ret);
}

int	ft_print_str(const char *format, int *ret)
{
	int	idx;
	int	chr_idx;

	idx = 0;
	if (ft_strchr_idx(format, '%') != -1)
		chr_idx = ft_strchr_idx(format, '%');
	else
		chr_idx = ft_strlen(format);
	while (idx < chr_idx)
	{
		write(1, &format[idx], 1);
		idx++;
	}
	*ret += chr_idx;
	return (chr_idx);
}

int	ft_printf(const char *format, ...)
{
	t_flag	container;
	va_list	vl;
	int		idx;
	int		ret;

	idx = 0;
	ret = 0;
	va_start(vl, format);
	if (!format)
		idx = -1;
	while (idx >= 0 && format[idx] != '\0')
	{
		if (format[idx] == '%')
		{
			idx += ft_store_to_container(&format[idx], &container);
			ret += ft_print_format(container, vl);
		}
		else
			idx += ft_print_str(&format[idx], &ret);
	}
	va_end(vl);
	return (ret);
}
