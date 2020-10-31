/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_sleep.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 21:05:54 by awerebea          #+#    #+#             */
/*   Updated: 2020/10/31 21:13:46 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <unistd.h>

void				f_sleep(int t)
{
	int				delta;
	int				start;

	start = get_time_in_ms();
	delta = 0;
	while (delta < t)
	{
		delta = get_time_in_ms() - start;
		usleep(100);
	}
}
