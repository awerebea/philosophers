/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 23:47:32 by awerebea          #+#    #+#             */
/*   Updated: 2020/10/28 23:28:36 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdlib.h>

static int		init_ph(t_data *data, t_ph *ph, int i)
{
	ph->id = i + 1;
	ph->times_to_eat = data->times_to_eat;
	ph->data = data;
	return (0);
}

int				start_threads(t_data *data)
{
	t_ph		*ph;
	pthread_t	*threads;
	int			i;

	i = 0;
	if (!(ph = (t_ph*)malloc(sizeof(t_ph) * data->num_of_ph)))
		return (ret_msg("error: malloc fails\n", 1));
	if (!(threads = (pthread_t*)malloc(sizeof(pthread_t) * data->num_of_ph)))
		return (ret_msg("error: malloc fails\n", 1));
	while (i < data->num_of_ph)
	{
		init_ph(data, &ph[i], i);
		pthread_create(&threads[i], NULL, simulation, &ph[i]);
		i++;
	}
	i = 0;
	while (i < data->num_of_ph)
	{
		pthread_join(threads[i], NULL);
		pthread_mutex_destroy(&data->mtx_forks[i]);
		i++;
	}
	return (0);
}
