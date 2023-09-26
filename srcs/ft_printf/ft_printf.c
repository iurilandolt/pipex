/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 23:24:35 by rlandolt          #+#    #+#             */
/*   Updated: 2023/09/26 11:46:50 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"

static int	check_arg(va_list args, const char c)
{
	int	fsize;

	fsize = 0;
	if (c == 'd' || c == 'i')
		fsize += ft_printnbr(va_arg(args, int));
	else if (c == 'c')
		fsize += ft_printchar(va_arg(args, int));
	else if (c == 's')
		fsize += ft_printstr(va_arg(args, char *));
	else if (c == 'u')
		fsize += ft_print_u_nbr(va_arg(args, unsigned int));
	else if (c == 'x' || c == 'X')
		fsize += ft_printhex(va_arg(args, unsigned int), c);
	else if (c == 'p')
		fsize += ft_printptr(va_arg(args, unsigned long long));
	else if (c == '%')
		fsize += ft_printchar('%');
	return (fsize);
}

int	ft_printf(const char *format, ...)
{
	int		fsize;
	va_list	args;

	fsize = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			fsize += check_arg(args, *format);
		}
		else
			fsize += ft_printchar(*format);
		format++;
	}
	va_end(args);
	return (fsize);
}
/*
#include <stdio.h>
int	main(void)
{
	int	ret1 = 0;
	int	ret2 = 0;
	float f1 = 3.2;
	unsigned int	hex = 420;
	char *str = NULL;

	ret1 = printf("og %d, %p, %x\n", ret1, &ret1, hex);
	printf("og %d\n", ret1);

	ret2 = ft_printf("ft %d, %p, %x\n", ret2, &ret2, hex);
	ft_printf("ft %d\n", ret2);

	ret1 = printf("%d\n", INT_MAX);
	printf("og %d\n", ret1);

	ret2 = ft_printf("%d\n", INT_MAX);
	ft_printf("ft %d\n", ret2);

	ret1 = printf("%s", str);
	printf("og %d\n", ret1);

	ret2 = ft_printf("%s", str);
	ft_printf("ft %d\n", ret2);
}
*/
