/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 23:47:32 by awerebea          #+#    #+#             */
/*   Updated: 2020/10/30 15:23:33 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdlib.h>

static void		init_ph(t_data *data, t_ph *ph, int i)
{
	ph->id = i + 1;
	ph->times_to_eat = data->times_to_eat;
	ph->data = data;
}

int				start_threads(t_data *data)
{
	t_ph		*ph;
	pthread_t	*threads;
	int			i;

	i = -1;
	if (!(ph = (t_ph*)malloc(sizeof(t_ph) * data->num_of_ph)) \
		|| !(threads = (pthread_t*)malloc(sizeof(pthread_t) * data->num_of_ph)))
		return (1);
	while (++i < data->num_of_ph)
	{
		init_ph(data, &ph[i], i);
		if (pthread_create(&threads[i], NULL, simulation, &ph[i]))
			return (1);
	}
	i = -1;
	while (++i < data->num_of_ph)
	{
		if (pthread_join(threads[i], NULL))
			return (1);
		if (pthread_mutex_destroy(&data->mtx_forks[i]))
			return (1);
	}
	free(ph);
	free(threads);
	return (0);
}
