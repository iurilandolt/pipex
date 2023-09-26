/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:39:37 by rlandolt          #+#    #+#             */
/*   Updated: 2023/09/26 13:06:02 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/ft_printf.h"

static int	ft_putptr(unsigned long long i)
{
	int	fsize;

	fsize = 0;
	if (i >= 16)
	{
		fsize += ft_putptr(i / 16);
		fsize += ft_putptr(i % 16);
	}
	else
	{
		if (i <= 9)
			fsize += ft_printchar(i + '0');
		else
			fsize += ft_printchar((i - 10 + 'a'));
	}
	return (fsize);
}

int	ft_printptr(unsigned long long i)
{
	if (i == 0)
		return (ft_printstr("(nil)"));
	else
		return (ft_printstr("0x") + ft_putptr(i));
}
