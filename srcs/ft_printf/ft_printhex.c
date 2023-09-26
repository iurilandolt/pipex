/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:12:02 by rlandolt          #+#    #+#             */
/*   Updated: 2023/09/26 13:06:18 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/ft_printf.h"

static int	ft_puthex(unsigned int i, const char c)
{
	int	fsize;

	fsize = 0;
	if (i >= 16)
	{
		fsize += ft_puthex(i / 16, c);
		fsize += ft_puthex(i % 16, c);
	}
	else
	{
		if (i <= 9)
			fsize = ft_printchar(i + '0');
		else
		{
			if (c == 'x')
				fsize += ft_printchar((i - 10 + 'a'));
			else if (c == 'X')
				fsize += ft_printchar((i - 10) + 'A');
		}
	}
	return (fsize);
}

int	ft_printhex(unsigned int i, const char c)
{
	if (i == 0)
		return (ft_printchar('0'));
	else
		return (ft_puthex(i, c));
}
