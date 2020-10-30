/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 12:52:12 by awerebea          #+#    #+#             */
/*   Updated: 2020/10/27 22:27:39 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_putnbr_fd(int n, int fd)
{
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n = -n;
	}
	if (n / 10 == 0)
		ft_putchar_fd(n + '0', fd);
	else
	{
		ft_putnbr_fd((unsigned int)n / 10, fd);
		ft_putchar_fd((unsigned int)n % 10 + '0', fd);
	}
}
