/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 11:38:41 by rlandolt          #+#    #+#             */
/*   Updated: 2023/09/26 13:23:15 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/ft_printf.h"

int	main(void)
{
	int	ret1 = 0;
	int	ret2 = 0;
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
