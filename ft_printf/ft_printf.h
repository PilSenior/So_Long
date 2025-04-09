/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htekdemi <htekdemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 22:40:26 by htekdemi          #+#    #+#             */
/*   Updated: 2024/11/26 22:40:26 by htekdemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

int	ft_printf(const char *a, ...);
int	ft_putchar(char c);
int	ft_putnbr(long int c);
int	ft_putstr(char *s);
int	ft_hexdecimal(unsigned long int n, char h);
int	ft_adress(unsigned long int c);

#endif
