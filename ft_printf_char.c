/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasuda <mmasuda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 14:32:45 by mmasuda           #+#    #+#             */
/*   Updated: 2021/06/01 17:04:35 by mmasuda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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

int	ft_print_char_ptr(va_list vl, t_flag container)
{
	const char	*s;
	int			ret;

	s = (const char *)va_arg(vl, const char *);
	if (!s)
		s = "(null)";
	ret = ft_branch_by_flag_char(container, ft_strlen(s), s);
	return (ret);
}

int	ft_branch_by_flag_char(t_flag container, int len, const char *s)
{
	int	ret;

	ret = 0;
	if (container.flags[0] == 1)
		ret = ft_if_flag_0_is_1_char(container, ret, (char *)s, len);
	else
		ret = ft_if_flag_0_is_0_char(container, ret, (char *)s, len);
	return (ret);
}

int	ft_if_flag_0_is_0_char(t_flag container, int ret,
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
		if (container.precision == -1)
			container.precision = len;
		ret = container.precision;
		while (container.width-- - container.precision > 0)
			ret += ft_print_zero_or_space(container);
		while (container.precision-- > 0 && *s != '\0')
			ft_putchar(*s++);
	}
	return (ret);
}

int	ft_if_flag_0_is_1_char(t_flag container, int ret, char *s, int len)
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
		if (container.precision == -1)
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
