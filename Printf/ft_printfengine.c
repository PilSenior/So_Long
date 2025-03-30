/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printfengine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htekdemi <htekdemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 22:40:06 by htekdemi          #+#    #+#             */
/*   Updated: 2024/11/26 22:40:06 by htekdemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

int	ft_putnbr(long int c)
{
	int	l;
	int	ret;

	l = 0;
	ret = 0;
	if (c < 0)
	{
		if (ft_putchar('-') == -1)
			return (-1);
		c = -c;
		l++;
	}
	if (c > 9)
	{
		ret = ft_putnbr(c / 10);
		if (ret == -1)
			return (-1);
		l += ret;
	}
	if (ft_putchar((c % 10) + '0') == -1)
		return (-1);
	return (l + 1);
}

int	ft_putstr(char *s)
{
	int	i;
	int	l;

	i = 0;
	l = 0;
	if (s == NULL)
		return (ft_putstr("(null)"));
	while (s[i])
	{
		if (ft_putchar(s[i]) == -1)
			return (-1);
		i++;
		l++;
	}
	return (l);
}

int	ft_hexdecimal(unsigned long int n, char h)
{
	char	*y;
	int		l;
	int		ret;

	l = 0;
	ret = 0;
	y = "0123456789abcdef";
	if (h == '1')
		y = "0123456789ABCDEF";
	if (n >= 16)
	{
		ret = ft_hexdecimal((n / 16), h);
		if (ret == -1)
			return (-1);
		l += ret;
	}
	if (n || !n)
	{
		if (ft_putchar(y[(n % 16)]) == -1)
			return (-1);
		l++;
	}
	return (l);
}

int	ft_adress(unsigned long int c)
{
	int	l;
	int	ret;

	l = 0;
	ret = 0;
	if (c == 0)
		return (ft_putstr("(nil)"));
	ret = ft_putstr("0x");
	if (ret == -1)
		return (-1);
	l += ret;
	ret = ft_hexdecimal(c, '0');
	if (ret == -1)
		return (-1);
	l += ret;
	return (l);
}
