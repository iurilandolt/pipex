/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 11:21:37 by rlandolt          #+#    #+#             */
/*   Updated: 2023/09/26 11:53:35 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H

# define FT_PRINTF_H

# include "pipex.h"

int	ft_printchar(int c);
int	ft_printstr(char *str);
int	ft_printnbr(int n);
int	ft_print_u_nbr(unsigned int n);
int	ft_printhex(unsigned int i, const char c);
int	ft_printptr(unsigned long long i);
int	ft_printf(const char *format, ...);

#endif
