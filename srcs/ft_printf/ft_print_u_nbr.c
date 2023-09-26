/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_u_nbr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:52:34 by rlandolt          #+#    #+#             */
/*   Updated: 2023/09/26 13:22:03 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"

int	ft_print_u_nbr(unsigned int n)
{
	int	size;

	size = 0;
	if (n >= 10)
	{
		size += ft_print_u_nbr(n / 10);
		size += ft_print_u_nbr(n % 10);
	}
	else
		size += ft_printchar(n + '0');
	return (size);
}
