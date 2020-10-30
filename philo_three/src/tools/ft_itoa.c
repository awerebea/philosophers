/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 22:44:49 by awerebea          #+#    #+#             */
/*   Updated: 2020/10/30 18:29:42 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_itoa(int n)
{
	char			*str;
	int				i;
	int				m;
	unsigned int	num;

	i = 1;
	if (n < 0)
		i++;
	m = n;
	while (m /= 10)
		i++;
	if (!(str = malloc(sizeof(char) * (i + 1))))
		return (NULL);
	if (n < 0)
		str[0] = '-';
	num = (n < 0) ? ((unsigned int)n * -1) : (unsigned int)n;
	str[i--] = '\0';
	while (num >= 10)
	{
		str[i--] = num % 10 + '0';
		num /= 10;
	}
	str[i--] = num + '0';
	return (str);
}
